#pragma once

#include "AdjacentTile.hpp"
#include "Cell.hpp"
#include "Direction.hpp"

#include <SDL2/SDL.h>

namespace pacman
{

namespace Util
{

SDL_Surface *load_bmp(char const *path);

Direction getOpposite(Direction direction);

Cell convertToGrid(const Cell& cell);

Cell getCenter(const Cell cell);

Cell getCenter(const int x, const int y);

AdjacentTile getAdjacentTiles(int x, int y, Direction direction);

Cell getCurrentCell(int x, int y);

}
}
