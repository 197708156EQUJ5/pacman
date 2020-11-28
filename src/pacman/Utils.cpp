#include "pacman/Utils.hpp"

namespace pacman
{
    
SDL_Surface *load_bmp(char const *path)
{
    SDL_Surface *optimized_version = nullptr;
    SDL_Surface *image_surface = SDL_LoadBMP(path);

    if (!image_surface)
    {
        return 0;
    }

    optimized_version = SDL_ConvertSurface(image_surface, image_surface->format, 0);

    if (!optimized_version)
    {
        SDL_FreeSurface(image_surface);
        return 0;
    }

    SDL_FreeSurface(image_surface);

    return optimized_version;    
}

Direction getOpposite(Direction direction)
{
    if (direction == Direction::UP)
    {
        return Direction::DOWN;
    }
    else if (direction == Direction::DOWN)
    {
        return Direction::UP;
    }
}

}
