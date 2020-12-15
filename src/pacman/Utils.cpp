#include "pacman/Utils.hpp"

#include "pacman/Constants.hpp"

#include <cmath>

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

Cell getTileAhead(int x, int y, Direction direction, int tilesAhead)
{
    Cell center = getCenter(x, y);
    if (direction == Direction::UP)
    {
        return Cell{center.col, center.row - (tilesAhead * Constants::TILE_SIZE)};
    }
    else if (direction == Direction::LEFT)
    {
        return Cell{center.col - (tilesAhead * Constants::TILE_SIZE), center.row};
    }
    else if (direction == Direction::DOWN)
    {
        return Cell{center.col, center.row + (tilesAhead * Constants::TILE_SIZE)};
    }
    else if (direction == Direction::RIGHT)
    {
        return Cell{center.col + (tilesAhead * Constants::TILE_SIZE), center.row};
    }
    
    return getCenter(Cell{center.col, center.row});
}

Cell getCurrentCell(int x, int y)
{
    return Cell{Util::getCenter(x, y)};
}

float distance(int x1, int y1, int x2, int y2) 
{ 
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0); 
}

float generateRandom(int low, int high)
{
    srand(time(0));
    return low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high - low)));
}

Cell getSrcCellPointValue(int deadGhostCount)
{
    if (deadGhostCount == 1)
    {
        return Constants::PV_200;
    }
    else if (deadGhostCount == 2)
    {
        return Constants::PV_400;
    }
    else if (deadGhostCount == 3)
    {
        return Constants::PV_800;
    }
    else
    {
        return Constants::PV_1600;
    }
}

}
}
