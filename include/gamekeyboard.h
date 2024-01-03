#ifndef _GAMEKEYBOARD_H
#define _GAMEKEYBOARD_H

struct GameKeyboardMapping{
  char left[2];
  char right[2];
  char down[2];
  char hold[2];
  char rotateRight[2];
  char rotateLeft[2];
  char confirm;
};

struct GameKeyboard{
  char* type;
  struct GameKeyboardMapping mapping; 
};

void ConfigureGameKeyboardMapping(struct GameKeyboard* gameKeyboard, char* left, char* right, char* down, char* hold, char* rotateRight, char* rotateLeft, char confirm);

#endif