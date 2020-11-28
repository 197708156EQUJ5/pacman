#pragma once

#include "pacman/Ghost.hpp"

namespace pacman
{

class Clyde : public Ghost
{
public:

    Clyde(int x = ClydeConstants::START_COL * Constants::CHARACTER_SIZE,
            int y = ClydeConstants::START_ROW * Constants::CHARACTER_SIZE, 
            Direction direction = Direction::UP, bool isOddMove = false, bool isHome = true);
    ~Clyde() = default;
    
    int getSrcCol();
    int getSrcRow();
};

} // namespace pacman

