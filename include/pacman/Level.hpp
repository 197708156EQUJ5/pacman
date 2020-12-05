#pragma once

#include "pacman/AdjacentTile.hpp"
#include "pacman/Cell.hpp"
#include "pacman/Direction.hpp"

#include <cstdint>
#include <vector>
#include <iostream>

namespace pacman
{

class Level
{
public:
    
    static std::vector<Cell> LEVEL_1;
    static const std::vector<Cell> LEGAL_TILES;
    static const Cell GHOST_HOUSE_DOOR;
    static const Cell GH_DOWN_EMPTY_TILE;
    static const Cell GH_UP_EMPTY_TILE;

    static Cell& getCellType(int col, int row);
    static bool isLegalMove(Cell cell);
    static bool isGhostHouseDoor(Cell cell);
    static int getCellValue(Cell cell);
    static std::vector<Cell>& getLevel();
    static AdjacentTile getAdjacentTiles(int x, int y, Direction direction);
    
};

} // namespace pacman
