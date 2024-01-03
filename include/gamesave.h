#ifndef _GAMESAVE_H
#define _GAMESAVE_H

//File management, dynamic memory and string manipulation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Keyboard struct and keys
#include "gamekeyboard.h"

#define INVALID_SAVEFILE 0
#define VALID_SAVEFILE 1
#define CORRUPTED_SAVEFILE 2

#define GAME_SAVE_FILE_SIZE 64
#define GAME_SAVE_PARAMETER_TYPE_SIZE 2
#define GAME_SAVE_PARAMETER_VALUE_SIZE 8

struct SaveFile{
  struct GameKeyboard gameKeyboard;
  char highScore[9];
  char* path;
};

void ChangeGameSaveFilePath(struct SaveFile* saveFile, char* saveFilePath);

int OverwriteGameSaveFile(char* saveFileContent, char* saveFilePath);
int ReadGameSaveFile(char* saveFileContent, char* saveFilePath);

int LoadGameSave(struct SaveFile* saveFile);
int SaveGameSave(struct SaveFile* saveFile);

#endif