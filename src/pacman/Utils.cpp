#include "pacman/Utils.hpp"

#include "pacman/Constants.hpp"

namespace pacman
{
    
namespace Util
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
    
Cell convertToGridSpace(const Cell& cell)
{
    return Cell{cell.col / Constants::TILE_SIZE, (cell.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE};
}

Cell getCenter(const int x, const int y)
{
    return Cell{((x / Constants::TILE_SIZE) * Constants::TILE_SIZE) + 4, ((y / Constants::TILE_SIZE) * Constants::TILE_SIZE) + 4};
}

}
}
