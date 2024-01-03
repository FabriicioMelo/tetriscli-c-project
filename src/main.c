#include "game.h"

int main()
{
  struct GameWindow* window = (struct GameWindow*)malloc(sizeof(struct GameWindow));
  ConfigureGameWindow(window, 638, 29);

  struct SaveFile* saveFile = (struct SaveFile*)malloc(sizeof(struct SaveFile));
  LoadGameSave(saveFile);

  printf("Highscore=%s\r\n", saveFile->highScore);
  printf("Keyboard =%s\r\n", saveFile->gameKeyboard.type);

  return 0;
}

void DrawGameInterface(struct GameWindow* window)
{
  strcpy(window->buffer.value, "+------------+----------+---+|            |          |   ||   STATS    |          |   ||            |          |   ||   I-XXXX   |          |   ||   O-XXXX   |          |   ||   T-XXXX   |          |   ||   J-XXXX   |          |   ||   L-XXXX   |          |   ||   S-XXXX   |          |   ||   Z-XXXX   |          |   ||            |          |   ||   HOLDING  |          |   ||     (X)    |          |   ||            |          |   ||   TOP      |          |   ||   XXXXXX   |          |   ||   SCORE    |          |   ||   XXXXXX   |          |   ||            |          |   ||            |          |   |+------------+----------+---+");
  DrawGameWindow(window);
}

void RunMenu(struct GameWindow* window)
{
  while(1)
  {
    char key = ReadGameKeyboardInput();
    
    if(key == 0) continue;

    printf("%d ('%c')\r\n", key, key);
  }
}