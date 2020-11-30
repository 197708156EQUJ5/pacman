#pragma once

#include "pacman/Ghost.hpp"

namespace pacman
{

class Inky : public Ghost
{
public:

    Inky(int x = InkyConstants::START_COL * Constants::CHARACTER_SIZE,
            int y = InkyConstants::START_ROW * Constants::CHARACTER_SIZE, 
            Direction direction = Direction::UP, bool isHome = true);
    ~Inky() = default;
    
    int getSrcCol();
    int getSrcRow();
};

} // namespace pacman

