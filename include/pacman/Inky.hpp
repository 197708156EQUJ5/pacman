#pragma once

#include "pacman/Ghost.hpp"

namespace pacman
{

class Inky : public Ghost
{
public:

    Inky(int x = InkyConstants::START_COL * Constants::CHARACTER_SIZE,
            int y = InkyConstants::START_ROW * Constants::CHARACTER_SIZE, 
            Direction direction = Direction::UP, bool isOddMove = false);
    ~Inky() = default;
    
    int getSrcCol();
    int getSrcRow();
    void move();
    void changeDirection(Direction direction);
};

} // namespace pacman

