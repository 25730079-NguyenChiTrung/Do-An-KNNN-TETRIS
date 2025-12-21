#ifndef DISPLAY_H
#define DISPLAY_H

#include "structs.h"

void clearScreen();

void draw(GameState &game);

void drawGameOver(GameState &game);

#endif