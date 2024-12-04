#ifndef Q7_H
#define Q7_H

#define PROMPT "enseash % "
#define BYE "Bye Bye\n"
#define MAXSIZE 1024
#define MSG_EXIT "[exit:%d|%dms]\n"
#define MSG_SIGN "[sign:%d|%dms]\n"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h> //open

// Include Q5.h to use the timer functions and global variables
#include "Q5.h"

// Function declarations for Q7
void Q7();
void display_mess3(const char *text, int val1, int val2);

#endif // Q7_H
