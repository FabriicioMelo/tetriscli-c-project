#ifndef _GAMEWINDOWCLI_H
#define _GAMEWINDOWCLI_H

//Dynamic memory and change of terminal flags
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

//Error Handling
#include <errno.h>

//Printing and
#include <stdio.h>

//String manipulation
#include <string.h>

//Clear screen
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

#define TERMINAL_ERROR (-1)

struct GameWindowBuffer{
  char* value;
  int size;
};

struct GameWindow{
  struct GameWindowBuffer buffer;
  int lineLength;
  int bufferDefined;
};

char ReadGameKeyboardInput();

void ConfigureGameWindowBuffer(struct GameWindow* window, int bufferSize, int lineLength);
void ConfigureGameWindow(struct GameWindow* window, int bufferSize, int lineLength);
void ChangeGameWindowBuffer(struct GameWindow* window, int initialIndexOfChange, char* newBufferValue);
void DrawGameWindow(struct GameWindow* window);

#endif