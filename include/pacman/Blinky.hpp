#pragma once

#include "pacman/Ghost.hpp"

namespace pacman
{

class Blinky : public Ghost
{
public:

    Blinky(int x = BlinkyConstants::START_COL * Constants::CHARACTER_SIZE,
            int y = BlinkyConstants::START_ROW * Constants::CHARACTER_SIZE, 
            Direction direction = Direction::LEFT, bool isOddMove = false);
    ~Blinky() = default;
    
    int getSrcCol();
    int getSrcRow();
    void move();
    void changeDirection(Direction direction);
};

} // namespace pacman

