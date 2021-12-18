#include "Tile.h"

Tile::Tile()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mState = TILE_STATE_FREE;

    alpha = 255;
}

void Tile::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void Tile::handleEvent(SDL_Event* e)
{
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + 100 )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > mPosition.y + 100 )
        {
            inside = false;
        }

        if (!inside)
        {
            alpha = 255;
        }
        else
        {
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                if (mState == TILE_STATE_FREE)
                {
                    alpha = 150;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                alpha = 255;
                break;

            case SDL_MOUSEBUTTONUP:
                if (mState == TILE_STATE_FREE)
                {
                    mState = gPlayer;

                    if (gPlayer == TILE_STATE_PLAYER_X)
                    {
                        gPlayer = TILE_STATE_PLAYER_O;
                    }
                    else
                    {
                        gPlayer = TILE_STATE_PLAYER_X;
                    }
                }
                
                alpha = 255;
                break;
            
            default:
                break;
            }

        }
        
    }
}

void Tile::render()
{
    gSpriteSheet.setAlpha(alpha);
    gSpriteSheet.render(mPosition.x, mPosition.y, &gSpriteClips[SPRITE_CLIP_TILE]);

    if (mState != TILE_STATE_FREE)
    {
        gSpriteSheet.render(mPosition.x, mPosition.y, &gSpriteClips[mState]);
    }
    
}

TILE_STATE Tile::getState()
{
    return mState;
}