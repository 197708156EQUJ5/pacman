#pragma once

#include "pacman/Utils.hpp"
#include "pacman/Constants.hpp"

#include <SDL2/SDL.h>

namespace pacman
{

class SpriteSheet
{
public:

    SpriteSheet(char const *path = Constants::SPRITESHEET_PATH, int column = Constants::SS_COLS, 
            int row = Constants::SS_ROWS);
            
    ~SpriteSheet();

    void selectSprite(int x, int y);
    void drawSelectedSprite(SDL_Surface *window_surface, SDL_Rect *position);

private:
    
    SDL_Rect clip;
    SDL_Surface *spriteSheetSurface;

    int m_start_x;
    int m_start_y;
};

} // namespace
