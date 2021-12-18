#include "TextTexture.h"

LTextTexture::LTextTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTextTexture::~LTextTexture()
{
	//Deallocate
	free();
}

bool LTextTexture::loadFromRenderedText( std::string textureText )
{
	//Get rid of preexisting texture
    free();

	SDL_Color textColor = {0, 0, 0, 255};

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return mTexture != NULL;
}

void LTextTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTextTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTextTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTextTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTextTexture::render(int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

int LTextTexture::getWidth()
{
	return mWidth;
}

int LTextTexture::getHeight()
{
	return mHeight;
}