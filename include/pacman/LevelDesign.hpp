#pragma once

#include <cstdint>
#include <vector>

namespace pacman
{

struct Cell
{
    int srcRow;
    int srcCol;
    int destRow;
    int destCol;
};

class LevelDesign
{
public:
    static const std::vector<Cell> LEVEL_1;

};

} // namespace pacman
