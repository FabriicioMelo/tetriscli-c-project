#ifndef _GAME_H
#define _GAME_H

#include <string.h>

#include "gamewindow.h"
#include "gamesave.h"
#include "gamekeyboard.h"

void DrawGameInterface(struct GameWindow* window);

void RunGame();

void RunMenu();

#endif