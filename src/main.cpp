#include "main.h"

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;

LSpriteSheet gSpriteSheet;

SDL_Rect gSpriteClips[SPRITE_CLIP_TOTAL];

LTextTexture gXwinsTextTexture;
LTextTexture gOwinsTextTexture;

Tile *tiles;

TILE_STATE gPlayer = TILE_STATE_PLAYER_X;

TILE_STATE winner = TILE_STATE_FREE;

int gXwins = 0;
int gOwins = 0;

int main(int argc, char* args[])
{
    if (!init())
    {
        printf("Failed to initialize!");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!");
        }
        else
        {
            bool quit = false;

            SDL_Event e;

            tiles = new Tile[BOARD_WIDTH * BOARD_HEIGHT];

            int k = 0;

            for (int i = 0; i < BOARD_WIDTH; i++)
            {
                for (int j = 0; j < BOARD_HEIGHT; j++)
                {
                    tiles[k].setPosition(i * 100, j * 100);
                    k++;
                }
                
            }
            

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
                    {
                        tiles[i].handleEvent(&e);
                    }
                    
                }

                winner = checkForWinner();

                if (winner != TILE_STATE_FREE)
                {
                    restart();
                }

                if (checkForDraw())
                {
                    restart();
                }
                
                

                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
                {
                    tiles[i].render();
                }

                gSpriteSheet.setAlpha(255);

                gSpriteSheet.render(300 + 50, 25, &gSpriteClips[SPRITE_CLIP_X]);

                gSpriteSheet.render(300 + 50, SCREEN_HEIGHT - 125, &gSpriteClips[SPRITE_CLIP_O]);

                gXwinsTextTexture.render(500, 25 + 50 - gXwinsTextTexture.getHeight() / 2);

                gOwinsTextTexture.render(500, SCREEN_HEIGHT - 25 - 50 - gOwinsTextTexture.getHeight() / 2);

                SDL_RenderPresent(gRenderer);
            }
            
        }
        
    }

    terminate();

    return 0;
}

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO/* | SDL_INIT_AUDIO*/) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }

                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }

                /*if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_Mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
                */
                
            }
            
        }
        
    }
    
    return success;
}



bool loadMedia()
{
    bool success = true;

    if (!(gSpriteSheet.loadFromFile("res/textureSheet.png")))
    {
        printf("Failed to load spritesheet! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gSpriteSheet.setBlendMode(SDL_BLENDMODE_BLEND);

        gSpriteClips[SPRITE_CLIP_TILE].x = 0;
        gSpriteClips[SPRITE_CLIP_TILE].y = 0;
        gSpriteClips[SPRITE_CLIP_TILE].w = 100;
        gSpriteClips[SPRITE_CLIP_TILE].h = 100;

        gSpriteClips[SPRITE_CLIP_X].x = 0;
        gSpriteClips[SPRITE_CLIP_X].y = 100;
        gSpriteClips[SPRITE_CLIP_X].w = 100;
        gSpriteClips[SPRITE_CLIP_X].h = 100;

        gSpriteClips[SPRITE_CLIP_O].x = 0;
        gSpriteClips[SPRITE_CLIP_O].y = 200;
        gSpriteClips[SPRITE_CLIP_O].w = 100;
        gSpriteClips[SPRITE_CLIP_O].h = 100;
    }

    gFont = TTF_OpenFont( "res/OfficialBook.ttf", 50 );
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    if( !gXwinsTextTexture.loadFromRenderedText( std::to_string(gXwins) ) )
    {
        printf( "Unable to render X texture!\n" );
    }

    if( !gOwinsTextTexture.loadFromRenderedText( std::to_string(gOwins) ) )
    {
        printf( "Unable to render O texture!\n" );
    }

    return success;
    
}



void terminate()
{
    gSpriteSheet.free();

    TTF_CloseFont(gFont);
    gFont = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

TILE_STATE checkForWinner()
{
    const int winningScores[] = {7, 56, 448, 73, 146, 292, 84, 273};

    TILE_STATE winner = TILE_STATE_FREE;

    int scoreX = calculateScore(TILE_STATE_PLAYER_X);
    int scoreO = calculateScore(TILE_STATE_PLAYER_O);

    for (int i = 0; i < 8; i++)
    {
        if ((winningScores[i] & scoreX) == winningScores[i])
        {
            winner = TILE_STATE_PLAYER_X;

            gXwins++;

            if( !gXwinsTextTexture.loadFromRenderedText( std::to_string(gXwins) ) )
            {
                printf( "Unable to render X texture!\n" );
            }
        }
        else if ((winningScores[i] & scoreO) == winningScores[i])
        {
            winner = TILE_STATE_PLAYER_O;

            gOwins++;

            if( !gOwinsTextTexture.loadFromRenderedText( std::to_string(gOwins) ) )
            {
                printf( "Unable to render O texture!\n" );
            }
        }
        
    }

    return winner;
}

int calculateScore(TILE_STATE player)
{
    int score = 0;

    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    {
        if (tiles[i].getState() == player)
        {
            score += 1 << i;
        }
        
    }

    return score;
    
}

bool checkForDraw()
{
    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    {
        if (tiles[i].getState() == TILE_STATE_FREE)
        {
            return false;
        }
        
    }

    if (winner != TILE_STATE_FREE)
    {
        return false;
    }
    
    return true;
}

void restart()
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    {
        tiles[i].render();
    }

    gSpriteSheet.setAlpha(255);

    gSpriteSheet.render(300 + 50, 25, &gSpriteClips[SPRITE_CLIP_X]);

    gSpriteSheet.render(300 + 50, SCREEN_HEIGHT - 125, &gSpriteClips[SPRITE_CLIP_O]);

    gXwinsTextTexture.render(500, 25 + 50 - gXwinsTextTexture.getHeight() / 2);

    gOwinsTextTexture.render(500, SCREEN_HEIGHT - 25 - 50 - gOwinsTextTexture.getHeight() / 2);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(1000);

    tiles = NULL;

    tiles = new Tile[BOARD_WIDTH * BOARD_HEIGHT];

    int k = 0;

    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            tiles[k].setPosition(i * 100, j * 100);
            k++;
        }
        
    }

}