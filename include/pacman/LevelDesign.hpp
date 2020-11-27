#pragma once

#include <cstdint>
#include <vector>

namespace pacman
{

struct Cell
{
    int srcCol;
    int srcRow;
};

class LevelDesign
{
public:
    static const std::vector<Cell> LEVEL_1;
    static const std::vector<Cell> LEGAL_TILES;

};

} // namespace pacman
