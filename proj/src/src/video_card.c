#include <lcom/lcf.h>

#include "../include/video_card.h"
#include "../include/character.h"
#include "../include/crosshair.h"
#include "../include/terrain.h"


static vbe_mode_info_t mem_info;
static void * video_mem ;   /*frame-buffer VM address*/
static mmap_t mem_map;
static uint32_t* second_buff;

int set_graphics_card_mode(uint16_t mode) { 

  //start memory map
  memset(&mem_info, 0, sizeof(mem_info)); //clear mem_info


  if (vbe_mode_info(mode,&mem_info) != 0) {
    printf("Failed to get vbe info\n");
    return 1;
  }


  int r;
  struct minix_mem_range mr; /*physical memory range*/
  unsigned int vram_base = mem_info.PhysBasePtr;  /*VRAM’s physical addresss*/
  unsigned int vram_size = mem_info.XResolution*mem_info.YResolution*(mem_info.BitsPerPixel/8);  /*VRAM’s size, but you can use the frame-buffer size, instead*/

  /*Allow memory mapping*/

  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  /*Map memory*/

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED)
  panic("couldn’t map video memory");

  second_buff = (uint32_t*) calloc(vram_size,sizeof(uint32_t));

  //inicialize graphic mode
  struct reg86u reg86;

  memset(&reg86, 0, sizeof(reg86));  //clears reg86;

  reg86.u.b.intno = BIOS_VIDEO;
  reg86.u.b.ah = CALL_VBE;
  reg86.u.b.al = VBE_SET_MODE;
  reg86.u.w.bx = LINEAR_FRAME_FUFFER | CLEAR_DISPLAY_MEM | mode;

  if (sys_int86(&reg86) != 0) {
    printf("sys_int86 failed\n");
    return 1;
  }


  return 0;
}

int free_mem() {
  lm_free(&mem_map);

  return 0;
}

int free_second_buf() {
  free(second_buff);
  
  return 0;
}

void set_background_green() {
  for (int i = 0; i < mem_info.XResolution; i++) {
    for (int j = 0; j < mem_info.YResolution; j++) {
      pixel_set_color(0xff00,i,j);
    }
  }
}


int pixel_set_color(uint32_t color, uint16_t hor, uint16_t vert) {
  if (hor >= mem_info.XResolution || vert >= mem_info.YResolution) {
    //printf("pixel_set_color: invalid parameters\n");
    return 0;
  }

  if (color == 0xff000000 | color == 0x0) {
    return 0;
  }

  /*
  uint32_t multiplier = mem_info.BitsPerPixel/8; //number of bytes per pixel
  void *pixelAdd = (void*) ((uint8_t*)video_mem + hor*multiplier + vert*mem_info.XResolution*multiplier); //just a trick to use pointer aritmetic
  memcpy(pixelAdd, &color, multiplier);
  */

 uint32_t* pixelAdd = second_buff + hor + vert*mem_info.XResolution;

  memcpy(pixelAdd, &color,sizeof(uint32_t));


  return 0;
}

int copy_to_sec_buf(uint32_t* mem) {
  memcpy(second_buff,mem,mem_info.XResolution*mem_info.YResolution*4);

  return 0;
}

uint32_t get_sec_buf_content(uint32_t pos) {
  return *(second_buff + pos);
}

uint32_t* create_mem_buf() {
  unsigned int vram_size = mem_info.XResolution*mem_info.YResolution*(mem_info.BitsPerPixel/8);
  uint32_t* buf = (uint32_t*) calloc(vram_size,sizeof(uint32_t));

  return buf;
}

int set_black_screen() {
  unsigned int vram_size = mem_info.XResolution*mem_info.YResolution*(mem_info.BitsPerPixel/8);
  memset(second_buff,0,vram_size);
  return 0;
}


int screen_refresh() {
  crosshair_draw();

  memcpy(video_mem,second_buff, mem_info.XResolution*mem_info.YResolution*4);

  return 0;
}

int screen_refresh_no_crosshair() {
  memcpy(video_mem,second_buff, mem_info.XResolution*mem_info.YResolution*4);

  return 0;
}


int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len; i++) {
    if (pixel_set_color(color,x+i,y) != 0) {
      return 1;
    }

    //printf("Pixel (%d, %d) set\n",x+i,y);
  }

  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (pixel_set_color(color,x+i,y+j) != 0) {
        return 1;
      }
    }

    // if (vg_draw_hline(x,y+i,width,color) != 0) {
    //   vg_exit();
    //   free_mem();
    //   printf("Failed to draw rectangle");
    //   return 1;
    // }
  }

  return 0;
}


int vbe_mode_info(uint16_t mode, vbe_mode_info_t* mode_info_p) {

  if (mode < 0x100) {
    printf("vbe_mode_info:Invalid mode\n");
    return 1;
  }

  struct reg86u reg86;

  lm_init(true);
  lm_alloc(sizeof(vbe_mode_info_t),&mem_map);

  memset(&reg86, 0, sizeof(reg86));  //clears reg86;

  reg86.u.b.intno = BIOS_VIDEO;
  reg86.u.b.ah = CALL_VBE;
  reg86.u.b.al = GET_MODE_INFO;
  reg86.u.w.cx = mode;
  reg86.u.w.es = PB2BASE(mem_map.phys);
  reg86.u.w.di = PB2OFF(mem_map.phys);

  if (sys_int86(&reg86) != 0) {
    lm_free(&mem_map);
    printf("vbe_mode_info:Failed to allocate low memory\n");
    return 1;
  }

  memcpy(mode_info_p,mem_map.virt,mem_map.size);

  return 0;
}

uint16_t get_XResolution() {
  return mem_info.XResolution;
}

uint16_t get_YResolution() {
  return mem_info.YResolution;
}

uint8_t get_BitsPerPixel() {
  return mem_info.BitsPerPixel;
}


uint32_t create_red_mask() {
  int pos = mem_info.RedFieldPosition;
  int size = mem_info.RedMaskSize;
  uint32_t mask = 0x1;

  for (int i = 1; i < size; i++) {
    mask = mask*2 +1;
  }

  return mask << pos;
}

uint32_t create_blue_mask() {
  int pos = mem_info.BlueFieldPosition;
  int size = mem_info.BlueMaskSize;
  uint32_t mask = 0x1;

  for (int i = 1; i < size; i++) {
    mask = mask*2 +1;
  }

  return mask << pos;
}

uint32_t create_green_mask() {
  int pos = mem_info.GreenFieldPosition;
  int size = mem_info.GreenMaskSize;
  uint32_t mask = 0x1;

  for (int i = 1; i < size; i++) {
    mask = mask*2 +1;
  }

  //printf("M:%x\n",mask);
  return mask << pos;
}

uint32_t R(uint16_t col, uint16_t step, uint32_t first) {
  return ((((first & create_red_mask()) >> mem_info.RedFieldPosition) + col * step) % (1 << mem_info.RedFieldPosition)) << mem_info.RedFieldPosition;
}

uint32_t G(uint16_t row, uint16_t step, uint32_t first) {
  return ((((first & create_green_mask()) >> mem_info.GreenFieldPosition) + row * step) % (1 << mem_info.GreenFieldPosition)) << mem_info.GreenFieldPosition;
}

uint32_t B(uint16_t col, uint16_t row, uint16_t step, uint32_t first) {
  return (((first & create_blue_mask()) >> mem_info.BlueFieldPosition) + (row + col)*step) << mem_info.BlueFieldPosition;
}

uint8_t index_col(uint16_t col,uint16_t row, uint16_t step, uint32_t first, uint8_t no_rectangles) {
  return (first + (row * no_rectangles + col) * step) % (1 << mem_info.BitsPerPixel);
}

int get_controller_info(vg_vbe_contr_info_t* info_p) {
  struct reg86u reg86;
  mmap_t ctrl_info;

  void * far_ptr_mult = lm_init(true);
  lm_alloc(sizeof(VbeInfoBlock_t),&ctrl_info);

  //vg_vbe_contr_info_t* ctrl_info_virt = (vg_vbe_contr_info_t*) ctrl_info.virt;

  VbeInfoBlock_t* ctrl_info_virt = (VbeInfoBlock_t*) ctrl_info.virt;

  ctrl_info_virt->VESASignature[0] = 'V';
  ctrl_info_virt->VESASignature[1] = 'B';
  ctrl_info_virt->VESASignature[2] = 'E';
  ctrl_info_virt->VESASignature[3] = '2';

  memset(&reg86, 0, sizeof(reg86));  //clears reg86;

  reg86.u.b.intno = BIOS_VIDEO;
  reg86.u.b.ah = CALL_VBE;
  reg86.u.b.al = GET_CONTR_INFO;
  reg86.u.w.es = PB2BASE(ctrl_info.phys);
  reg86.u.w.di = PB2OFF(ctrl_info.phys);

  if (sys_int86(&reg86) != 0) {
    lm_free(&ctrl_info);
    printf("vbe_mode_info:Failed to allocate low memory\n");
    return 1;
  }

  info_p->VBESignature[0] = ctrl_info_virt->VESASignature[0];
  info_p->VBESignature[1] = ctrl_info_virt->VESASignature[1];
  info_p->VBESignature[2] = ctrl_info_virt->VESASignature[2];
  info_p->VBESignature[3] = ctrl_info_virt->VESASignature[3];
  info_p->VBEVersion[0] = ctrl_info_virt->VBEVersion[0];
  info_p->VBEVersion[1] = ctrl_info_virt->VBEVersion[1];
  info_p->TotalMemory = 64*ctrl_info_virt->TotalMemory;

  //printf("%x\n",ctrl_info_virt->OEMStringPtr);

  //OEMStringPtr virtual adress
  uint32_t tmp_ptr = ctrl_info_virt->OEMStringPtr;
  uint32_t OEM_far_ptr = ((0xFFFF0000 & tmp_ptr)>>12) + (tmp_ptr & 0xFFFF) + ((uint32_t) far_ptr_mult);
  info_p->OEMString = (char *) OEM_far_ptr;

  //printf("%x\n",*ctrl_info_virt->OEMStringPtr);

  tmp_ptr = ctrl_info_virt->VideoModePtr;
  uint32_t video_far_ptr = ((0xFFFF0000 & tmp_ptr)>>12) + (tmp_ptr & 0xFFFF) + ((uint32_t) far_ptr_mult);
  info_p->VideoModeList = (uint16_t*) video_far_ptr;

  tmp_ptr = ctrl_info_virt->OEMVendorNamePtr;
  uint32_t vendor_far_ptr = ((0xFFFF0000 & tmp_ptr)>>12) + (tmp_ptr & 0xFFFF) + ((uint32_t) far_ptr_mult);
  info_p->OEMVendorNamePtr = (char *) vendor_far_ptr;

  tmp_ptr = ctrl_info_virt->OEMProductNamePtr;
  uint32_t prod_name_far_ptr = ((0xFFFF0000 & tmp_ptr)>>12) + (tmp_ptr & 0xFFFF) + ((uint32_t) far_ptr_mult);
  info_p->OEMProductNamePtr = (char*) prod_name_far_ptr;

  tmp_ptr = ctrl_info_virt->OEMProductRevPtr;
  uint32_t prod_rev_far_ptr = ((0xFFFF0000 & tmp_ptr)>>12) + (tmp_ptr & 0xFFFF) + ((uint32_t) far_ptr_mult);
  info_p->OEMProductRevPtr = (char *)prod_rev_far_ptr;

  lm_free(&ctrl_info);

  return 0;

}




