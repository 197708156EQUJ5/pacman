#pragma once

#include "pacman/Ghost.hpp"

namespace pacman
{

class Pinky : public Ghost
{
public:

    Pinky(int x = PinkyConstants::START_COL * Constants::CHARACTER_SIZE,
            int y = PinkyConstants::START_ROW * Constants::CHARACTER_SIZE, 
            Direction direction = Direction::DOWN, bool isOddMove = false);
    ~Pinky() = default;
    
    int getSrcCol();
    int getSrcRow();
    void move();
    void changeDirection(Direction direction);
};

} // namespace pacman

