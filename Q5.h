//
// Created by grimont on 04/12/24.
//
#ifndef Q5_H
#define Q5_H
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

// Timer functions
extern struct timespec start_time;
extern struct timespec end_time;

void Q5();
void start_timer();
void end_timer();
int get_time();

#endif //Q5_H
