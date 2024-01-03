#include "gamesave.h"

#define STRING_END_SPACE 1

void ChangeGameSaveFilePath(struct SaveFile* saveFile, char* saveFilePath)
{
  saveFile->path = saveFilePath;
}

int ReadGameSaveFile(char* saveFileContent, char* saveFilePath)
{
  FILE* saveFile = fopen(saveFilePath, "r");

  if(!saveFile) return INVALID_SAVEFILE;

  char saveFileBuffer;

  short saveFileCharIndex = 0;
  while(1)
  {
    saveFileBuffer = fgetc(saveFile);
    if(saveFileBuffer == EOF) break;

    saveFileContent[saveFileCharIndex] = saveFileBuffer;
    saveFileCharIndex++;
  }

  saveFileContent[saveFileCharIndex] = '\0';

  fclose(saveFile);
  return VALID_SAVEFILE;
}

int OverwriteGameSaveFile(char* saveFileContent, char* saveFilePath)
{

}

int LoadGameSave(struct SaveFile* saveFile)
{
  char* saveFileContent = (char*)malloc((GAME_SAVE_FILE_SIZE + STRING_END_SPACE) * sizeof(char));
  
  if(!saveFile->path) saveFile->path = "tetriscli.save";

  if(ReadGameSaveFile(saveFileContent, saveFile->path) == INVALID_SAVEFILE){
    printf("File doesnt exist!\n");
    return INVALID_SAVEFILE;
  }

  short gameSaveParameterSize = GAME_SAVE_PARAMETER_TYPE_SIZE + GAME_SAVE_PARAMETER_VALUE_SIZE;

  if((strlen(saveFileContent) % gameSaveParameterSize) != 0){
    printf("Save file has been corrupted");
    free(saveFileContent);
    return CORRUPTED_SAVEFILE;
  }

  int numberOfSaveFileParameters = 2;

  char saveFileParameterType[GAME_SAVE_PARAMETER_TYPE_SIZE + STRING_END_SPACE];
  char saveFileParameterValue[GAME_SAVE_PARAMETER_VALUE_SIZE + STRING_END_SPACE];

  for(short numberOfSaveFileParametersFound = 0; numberOfSaveFileParametersFound < numberOfSaveFileParameters; numberOfSaveFileParametersFound++)
  {
    for(short t = 0; t < GAME_SAVE_PARAMETER_TYPE_SIZE; t++){
      char saveFileTypeChar = saveFileContent[t + (gameSaveParameterSize * numberOfSaveFileParametersFound)];
      if(saveFileTypeChar < 47 || saveFileTypeChar > 57) return CORRUPTED_SAVEFILE;
      saveFileParameterType[t] = saveFileTypeChar;
    }

    for(int v = 0; v < GAME_SAVE_PARAMETER_VALUE_SIZE; v++){
      char saveFileValueChar = saveFileContent[v + GAME_SAVE_PARAMETER_TYPE_SIZE + (gameSaveParameterSize * numberOfSaveFileParametersFound)];
      if(saveFileValueChar < 47 || saveFileValueChar > 57) return CORRUPTED_SAVEFILE;
      saveFileParameterValue[v] = saveFileValueChar;
    }

    if(strcmp(saveFileParameterType, "01") == 0){
      strcpy(saveFile->highScore, saveFileParameterValue);
    }
    else if(strcmp(saveFileParameterType, "02") == 0){ 
      char gameKeyboardKeysA[2] = {'a', 'A'};
      char gameKeyboardKeysS[2] = {'s', 'S'};
      char gameKeyboardKeysD[2] = {'d', 'D'};
      char gameKeyboardKeysJ[2] = {'j', 'J'};
      char gameKeyboardKeysK[2] = {'k', 'K'};
      char gameKeyboardKeysL[2] = {'l', 'L'};
      char gameKeyboardKeySpace = ' ';

      if(strcmp(saveFileParameterValue, "00000001") == 0){
        ConfigureGameKeyboardMapping(&(saveFile->gameKeyboard), gameKeyboardKeysA, gameKeyboardKeysD, gameKeyboardKeysS, gameKeyboardKeysJ, gameKeyboardKeysL, gameKeyboardKeysK, gameKeyboardKeySpace);
        saveFile->gameKeyboard.type = saveFileParameterValue;
      }
      else if(strcmp(saveFileParameterValue, "00000002") == 0){
        ConfigureGameKeyboardMapping(&(saveFile->gameKeyboard), gameKeyboardKeysJ, gameKeyboardKeysL, gameKeyboardKeysK, gameKeyboardKeysD, gameKeyboardKeysS, gameKeyboardKeysA, gameKeyboardKeySpace);
        saveFile->gameKeyboard.type = saveFileParameterValue;
      }
      else{
        return CORRUPTED_SAVEFILE;
      }
    }
  }

  free(saveFileContent);

  return VALID_SAVEFILE;
}

int SaveGameSave(struct SaveFile* saveFile)
{

}
