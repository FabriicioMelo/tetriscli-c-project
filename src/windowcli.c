#include "windowcli.h"

void Die(const char *s)
{
  perror(s);
  exit(1);
}

struct termios orig_termios;

// THIS ...
void DisableTerminalRawMode()
{
  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) Die("tcsetattr");  
}

// THIS ...
void EnableTerminalRawMode()
{
  if(tcgetattr(STDIN_FILENO, &orig_termios) == -1) Die("tcgetattr");
  atexit(DisableTerminalRawMode);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
  raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) Die("tcsetattr");
}

char ReadKeyboardKey()
{
  char c = '\0';
  if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) Die("read");
  return c;
}

void ConfigureWindowCLIBuffer(struct WindowCLI* window, int bufferSize, int bufferEndLine)
{
  window->bufferSize = bufferSize;
  window->bufferEndLine = bufferEndLine;

  if(!window->buffer) free(window->buffer); 
  window->buffer = (char*)malloc(window->bufferSize * sizeof(char));

  for(int bufferDrawn = 0; bufferDrawn <= window->bufferSize; bufferDrawn++)
  {
    window->buffer[bufferDrawn] = ' ';
  }
}

void ConfigureWindowCLI(struct WindowCLI* window, int bufferSize, int bufferEndLine)
{
  EnableTerminalRawMode();
  ConfigureWindowCLIBuffer(window, bufferSize, bufferEndLine);
}

void DrawWindowCLI(struct WindowCLI* window)
{
  clrscr();
  for(int bufferDrawn = 0; bufferDrawn < window->bufferSize; bufferDrawn++)
  {
    //printf("%dP%d=%d\r\n ", bufferDrawn, window->bufferEndLine, (bufferDrawn+1) % window->bufferEndLine);
    if((bufferDrawn) % (window->bufferEndLine) == 0 && bufferDrawn != 0){
      //printf("LINE");
      printf("\r\n");
    }
    printf("%c", window->buffer[bufferDrawn]);
  }

  printf("\r\n");
}

/*
void ChangeInWindowCLIBuffer(struct WindowCLI* window, firstIndex, char* newBufferValue)
{
AAAAAAAAAAAAAAAAAAAAAAAAAAAA
}
*/