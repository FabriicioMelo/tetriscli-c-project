#include "gamekeyboard.h"

void ConfigureGameKeyboardMapping(struct GameKeyboard* gameKeyboard, char* left, char* right, char* down, char* hold, char* rotateRight, char* rotateLeft, char confirm)
{
  gameKeyboard->mapping.left[0] = left[0];
  gameKeyboard->mapping.left[1] = left[1];
  
  gameKeyboard->mapping.right[0] = right[0];
  gameKeyboard->mapping.right[1] = right[1];
  
  gameKeyboard->mapping.down[0] = down[0];
  gameKeyboard->mapping.down[1] = down[1];
  
  gameKeyboard->mapping.hold[0] = hold[0];
  gameKeyboard->mapping.hold[1] = hold[1];
  
  gameKeyboard->mapping.rotateRight[0] = rotateRight[0];
  gameKeyboard->mapping.rotateRight[1] = rotateRight[1];
  
  gameKeyboard->mapping.rotateLeft[0] = rotateLeft[0];
  gameKeyboard->mapping.rotateLeft[1] = rotateLeft[1];
  
  gameKeyboard->mapping.confirm = confirm;
}