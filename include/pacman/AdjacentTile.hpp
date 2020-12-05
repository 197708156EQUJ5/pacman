#pragma once

#include "pacman/Cell.hpp"

#include <vector>

namespace pacman
{

struct AdjacentTile
{
    Cell north;
    Cell east;
    Cell south;
    Cell west;

    std::vector<Cell> tiles{north, east, south, west};
};

}
