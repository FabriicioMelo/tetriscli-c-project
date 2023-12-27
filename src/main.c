#include "windowcli.h"

void RunGame();

int main()
{
  struct WindowCLI window;

  ConfigureWindowCLI(&window, 638, 29);

  printf("%d", window.bufferSize);

  RunGame(&window);

  return 0;

/*
DrawWindowCLI(&window);

while(1)
  {
    char key = ReadKeyboardKey();
    if(key != 0) printf("%d ('%c')\r\n", key, key);
  }
*/
}

void RunGame(struct WindowCLI* window)
{
  UpdateWindowCLIBuffer(window, 62, "STATS");
  DrawWindowCLI(window);
}