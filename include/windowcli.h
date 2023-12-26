#ifndef _WINDOWCLI_H
#define _WINDOWCLI_H

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

struct WindowCLI{
  char* buffer;
  int bufferSize;
  int bufferEndLine;
};

char ReadKeyboardKey();

void ConfigureWindowCLI(struct WindowCLI* window, int bufferSize, int bufferEndLine);
void DrawWindowCLI(struct WindowCLI* window);

#endif