#include <stdio.h>
#include <unistd.h>

#include "windowcli.h"

int main()
{
  struct WindowCLI window;

  ConfigureWindowCLI(&window, 638, 29);

  DrawWindowCLI(&window);

  //while(1)
  //{
  //  char key = ReadKeyboardKey();
    //if(key != 0) printf("%d ('%c')\r\n", key, key);
  //}

  return 0;
}

void DrawGame()
{

}

void DrawInfo()
{

}