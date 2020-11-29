#pragma once

#include "pacman/Cell.hpp"

#include <vector>

namespace pacman
{

struct AdjacentTile
{
    Cell nextTile;
    Cell prevTile;
    Cell northTile;
    Cell eastTile;
    Cell southTile;
    Cell westTile;

    std::vector<Cell> tiles{northTile, eastTile, southTile, westTile};
};

}
