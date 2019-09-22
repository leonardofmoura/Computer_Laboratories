PROG=proj

.PATH: ${.CURDIR}/src 

SRCS += kbd.c mouse.c timer.c video_card.c crosshair.c character.c terrain.c button.c event_manager.c rtc.c clock.c serial_port.c queue.c projectile.c enemy.c

SRCS += proj.c

CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
