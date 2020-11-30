#include "pacman/Blinky.hpp"

#include <iostream>

namespace pacman
{

Blinky::Blinky(int x, int y, Direction direction, bool isHome) : 
    Ghost(x, y, direction, isHome)
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

}
