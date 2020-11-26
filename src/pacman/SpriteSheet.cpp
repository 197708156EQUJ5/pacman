#include "pacman/SpriteSheet.hpp"

namespace pacman
{

SpriteSheet::SpriteSheet(char const *path, int col, int row)
{
    spriteSheetSurface = load_bmp(path);

    clip.w = spriteSheetSurface->w / col;
    clip.h = spriteSheetSurface->h / row;
}

SpriteSheet::~SpriteSheet()
{
    SDL_FreeSurface(spriteSheetSurface);
}

void SpriteSheet::selectSprite(int x, int y)
{
    clip.x = x * clip.w;
    clip.y = y * clip.h;
}

void SpriteSheet::drawSelectedSprite(SDL_Surface *windowSurface, SDL_Rect *position)
{
    SDL_BlitScaled(spriteSheetSurface, &clip, windowSurface, position);
    //SDL_BlitSurface(spriteSheetSurface, &clip, windowSurface, position);
}

} // namespace
