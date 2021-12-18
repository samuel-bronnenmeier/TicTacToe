#ifndef SDL_H
#define SDL_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#endif

#ifndef TEXTTEXTURE_H
#define TEXTTEXTURE_H

#include <string>

#include <Utils.h>

class LTextTexture
{
    public:
        public:
		//Initializes variables
		LTextTexture();

		//Deallocates memory
		~LTextTexture();

		//Loads image at specified path
		bool loadFromRenderedText(std::string textureText);

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