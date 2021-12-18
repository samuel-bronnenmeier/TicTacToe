#ifndef SDL_H
#define SDL_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#endif

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string>
#include <cmath>
#include <sstream>

#define TicTacToe_VERSION_MAJOR 1
#define TicTacToe_VERSION_MINOR 0
#define TicTacToe_PATCHLEVEL 0

#include "gSpriteSheet.h"

#include "Utils.h"

#include "Tile.h"

#include "SpriteSheet.h"

#include "TextTexture.h"

#include "Timer.h"

//Initialize the app and all libraries
bool init();

//Loads all media
bool loadMedia();

//Closes the app
void terminate();

//Checks for winner
TILE_STATE checkForWinner();

//Calculate the players' scores
int calculateScore(TILE_STATE player);

//Checks for draw
bool checkForDraw();

//Restarts the game (NOT the app)
void restart();

#endif