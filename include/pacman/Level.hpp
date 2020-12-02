#pragma once

#include "pacman/AdjacentTile.hpp"
#include "pacman/Cell.hpp"

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
    static Cell& getCellType(int col, int row);
    static bool isLegalMove(Cell cell);
    static bool isGhostHouseDoor(Cell cell);
    static int getCellValue(Cell cell);
    static std::vector<Cell>& getLevel();
    AdjacentTile getAdjacentTiles(int x, int y);
    
};

} // namespace pacman
