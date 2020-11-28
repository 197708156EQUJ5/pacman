#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

namespace pacman
{

struct Cell
{
    int col;
    int row;

    bool operator==(const Cell& rhs)
    {
        return col == rhs.col && row == rhs.row;
    }
};

class LevelDesign
{
public:
    static const std::vector<Cell> LEVEL_1;
    static const std::vector<Cell> LEGAL_TILES;

};

} // namespace pacman
