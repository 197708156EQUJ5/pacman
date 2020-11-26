#pragma once

#include <SDL2/SDL.h>
#include "pacman/Utils.hpp"

namespace pacman
{

class SpriteSheet
{
public:

    SpriteSheet(char const *path, int row, int column);
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
