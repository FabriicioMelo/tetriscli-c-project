#include "gamewindow.h"

void KillGameApplication(const char *reason)
{
  perror(reason);
  exit(1);
}

struct termios orig_termios;

// THIS ...
void DisableTerminalRawMode()
{
  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == TERMINAL_ERROR) KillGameApplication("tcsetattr");  
}

// THIS ...
void EnableTerminalRawMode()
{
  if(tcgetattr(STDIN_FILENO, &orig_termios) == TERMINAL_ERROR) KillGameApplication("tcgetattr");
  atexit(DisableTerminalRawMode);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
  raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 0.1;

  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == TERMINAL_ERROR) KillGameApplication("tcsetattr");
}

char ReadGameKeyboardInput()
{
  char c = '\0';
  if(read(STDIN_FILENO, &c, 1) == TERMINAL_ERROR && errno != EAGAIN) KillGameApplication("read");
  return c;
}

void ConfigureGameWindow(struct GameWindow* window, int bufferSize, int lineLength)
{
  EnableTerminalRawMode();
  ConfigureGameWindowBuffer(window, bufferSize, lineLength);
}

void ConfigureGameWindowBuffer(struct GameWindow* window, int bufferSize, int lineLength)
{
  window->buffer.size = bufferSize;
  window->lineLength = lineLength;

  if(window->bufferDefined == 1) free(window->buffer.value);
   
  window->buffer.value = (char*)malloc(window->buffer.size * sizeof(char));
  window->bufferDefined = 1;
}

void ChangeGameWindowBuffer(struct GameWindow* window, int initialIndexOfChange, char* newBufferValue)
{
  int newBufferValueLength = strlen(newBufferValue);
  if((initialIndexOfChange + newBufferValueLength) >= window->buffer.size) KillGameApplication("bufferupdate");
  for(int updatedValues = 0; updatedValues < newBufferValueLength; updatedValues++)
  {
    window->buffer.value[initialIndexOfChange + updatedValues] = newBufferValue[updatedValues];
  }
}

void ClearGameWindow()
{
  clrscr();
}

void DrawGameWindow(struct GameWindow* window)
{
  ClearGameWindow();
  for(int bufferCharDrawn = 0; bufferCharDrawn < window->buffer.size; bufferCharDrawn++)
  {
    if((bufferCharDrawn) % (window->lineLength) == 0 && bufferCharDrawn != 0){
      printf("\r\n");
    }
    printf("%c", window->buffer.value[bufferCharDrawn]);
  }
  printf("\r\n");
}