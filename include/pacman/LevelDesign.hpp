#pragma once

#include "pacman/Cell.hpp"

#include <cstdint>
#include <vector>
#include <iostream>

namespace pacman
{

class LevelDesign
{
public:
    static std::vector<Cell> LEVEL_1;
    static const std::vector<Cell> LEGAL_TILES;
    static Cell& getCellType(int col, int row);
    static bool canMove(Cell cell);
    static bool isLegalMove(Cell cell);
    static int getCellValue(Cell cell);
    static std::vector<Cell>& getLevel();

};

} // namespace pacman
