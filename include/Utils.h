#ifndef SDL_H
#define SDL_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#endif

#ifndef UTILS_H
#define UTILS_H

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 300;

const int BOARD_WIDTH = 3;
const int BOARD_HEIGHT = 3;

enum LSpriteClips
{
    SPRITE_CLIP_TILE,
    SPRITE_CLIP_X,
    SPRITE_CLIP_O,
    SPRITE_CLIP_TOTAL
};

enum TILE_STATE
{
    TILE_STATE_FREE,
    TILE_STATE_PLAYER_X,
    TILE_STATE_PLAYER_O
};

extern SDL_Window* gWindow;

extern SDL_Renderer* gRenderer;

extern TTF_Font* gFont;

extern SDL_Rect gSpriteClips[SPRITE_CLIP_TOTAL];

extern TILE_STATE gPlayer;

extern TILE_STATE winner;

#endif