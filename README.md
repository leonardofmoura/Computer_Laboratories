# FEUP-LCOM
Repository created for the LCOM course at FEUP.
The course conssists of several labs that are developed during lab classes, more info on each lab can be found bellow.
All the code in this repository was made strictly for educational purposes and you can use it as you please, just keep in mind I'm not responsibe for anything. If you are taking the LCOM course please keep in mind its strict policy in relation to copy. If you are taking the course and find yourself here in need for help, I recomend you check out my code (or any other student's) and try to figure out what's happening (using the lecture slides for example), then try to do it on your own way, using your own coding style. That's the only way you are really going to learn something! 

**Everything developed during this course was done with the help of my partner** (João Ribeiro)[github.com/Fujicsso]

## Lab0 - Introduction
This lab serves as quick introduction to the course and C programming. It is also serves as a first contact with the MINIX operating system and a version control system (in my case SVN).

## Lab2 - The Timer
This is the first real lab in the LCOM course, it addresses the i8254 Timer/Counter, an I/O device that can be used to measure time intervals. It is also the first contact with programming an I/O device and using interrupts.

## Lab3 - The Keyboard 
This lab adresses the i8042 KBC controller. One of the purposes of the lab is to be able the read makecodes and breakcodes of several keys of the keyboard using interrupts. It also mixes C programming with Assembly programming for the first time in the course.

## Lab4 - The Mouse
This lab adresses the PS/2 Mouse. In this lab we write functions that interface with the mouse via the KBC. In this lab we have process mouse interrupts (this requires dealing with multiple asynchronous interrupts), as well as read mouse packets. We also use a state machine to detect when a specific pattern is drawn with the mouse.

## Lab5 - The Video Card
This lab adresses the Video Card in Graphics Mode. We have to configure the Graphic mode to the Video Card in order to use it. We do that by using the VESA Bios Extension (VBE). For the first time in the course we have to proform BIOS calls and map Physical Memory to a virtual adress space (Virtual Memory).

## Proj - Foolish Chaos
Foolish chaos is a roguelike arcade game. You play as the main character: *The Fool*. You spawn in a procedurely generated themed map and enemies are coming your way! You have to do whatever it takes to survive (i.e kill 'em all). The game engine is fully implemented, but we have some features planned we did not have the time to implement at the time of the project deadline. So, who knows? We might work on it again sometime!
On an important note, all the sprites of the game are original creations of my partner (João)[github.com/Fujicsso].



**Note**:If find some mistake in this readme or any other part of this repo, feel free to tell me about it!

*README version 1.2*