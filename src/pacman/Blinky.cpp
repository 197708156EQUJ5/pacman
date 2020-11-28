#include "pacman/Blinky.hpp"

#include <iostream>

namespace pacman
{

Blinky::Blinky(int x, int y, Direction direction, bool isOddMove) : 
    Ghost(x, y, direction, isOddMove)
{
}

int Blinky::getSrcCol()
{
    int srcCol = -1;

    if (direction == Direction::LEFT)
    {
        srcCol = isOddMove ? BlinkyConstants::SRC_LEFT_1 : BlinkyConstants::SRC_LEFT_2;
    }
    else if (direction == Direction::RIGHT)
    {
        srcCol = isOddMove ? BlinkyConstants::SRC_RIGHT_1 : BlinkyConstants::SRC_RIGHT_2;
    }
    if (direction == Direction::UP)
    {
        srcCol = isOddMove ? BlinkyConstants::SRC_UP_1 : BlinkyConstants::SRC_UP_2;
    }
    else if (direction == Direction::DOWN)
    {
        srcCol = isOddMove ? BlinkyConstants::SRC_DOWN_1 : BlinkyConstants::SRC_DOWN_2;
    }

    return srcCol;
}

int Blinky::getSrcRow()
{
    return BlinkyConstants::SRC_ROW;
}

void Blinky::move()
{
    if (direction == Direction::LEFT)
    {
        x -= 9;
    }
    else if (direction == Direction::RIGHT)
    {
        x += 9;
    }
    else if (direction == Direction::DOWN)
    {
        y += 9;
    }
    else if (direction == Direction::UP)
    {
        y -= 9;
    }
    isOddMove = !isOddMove;    
}

void Blinky::changeDirection(Direction direction)
{
    this->direction = direction;
}

}
