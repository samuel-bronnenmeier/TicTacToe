#ifndef SDL_H
#define SDL_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#endif

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <string>

#include "Utils.h"

//Class for wrapping spritesheet
class LSpriteSheet
{
    public:
		//Initializes variables
		LSpriteSheet();

		//Deallocates memory
		~LSpriteSheet();

		//Loads image at specified path
		bool loadFromFile(std::string path);

		//Deallocates texture
		void free();

		//Modulate the color
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blend mode
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha channel
		void setAlpha(Uint8 alpha);

		//Renders texture at given point
		void render(int x, int y, SDL_Rect* clip = NULL);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif