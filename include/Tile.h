#ifndef SDL_H
#define SDL_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#endif

#ifndef TILE_H
#define TILE_H

#include "Utils.h"

#include "gSpriteSheet.h"

class Tile
{
    public:
		//Initializes internal variables
		Tile();

		//Sets top left positon
		void setPosition(int x, int y);

		//Handles mouse event
		void handleEvent(SDL_Event* e);

		//Shows button sprite
		void render();

        //Get the tile's state
        TILE_STATE getState();

        Uint8 alpha;

	private:
		//Top left position
		SDL_Point mPosition;

        //State (free, O or X)
        TILE_STATE mState;
};

#endif