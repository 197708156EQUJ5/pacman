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
    
Cell convertToGrid(const Cell& cell)
{
    return Cell{cell.col / Constants::TILE_SIZE, (cell.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE};
}

Cell getCenter(Cell cell)
{
    return getCenter(cell.col, cell.row);
}

Cell getCenter(int x, const int y)
{
    return Cell{((x / Constants::TILE_SIZE) * Constants::TILE_SIZE) + 4, ((y / Constants::TILE_SIZE) * Constants::TILE_SIZE) + 4};
}

AdjacentTile getAdjacentTiles(int x, int y, Direction direction)
{
    int adjacentX = x;
    int adjacentY = y;

    if (direction == Direction::LEFT)
    {
        adjacentX -= Constants::TILE_SIZE;
    }
    else if (direction == Direction::RIGHT)
    {
        adjacentX += Constants::TILE_SIZE;
    }
    else if (direction == Direction::UP)
    {
        adjacentY -= Constants::TILE_SIZE;
    }
    else if (direction == Direction::DOWN)
    {
        adjacentY += Constants::TILE_SIZE;
    }

    const Cell north{Util::getCenter(adjacentX, adjacentY - Constants::TILE_SIZE)};
    const Cell south{Util::getCenter(adjacentX, adjacentY + Constants::TILE_SIZE)};
    const Cell east{Util::getCenter(adjacentX + Constants::TILE_SIZE, adjacentY)};
    const Cell west{Util::getCenter(adjacentX - Constants::TILE_SIZE, adjacentY)};
   
    return {north, east, south, west};
}

Cell getCurrentCell(int x, int y)
{
    return Cell{Util::getCenter(x, y)};
}

}
}
