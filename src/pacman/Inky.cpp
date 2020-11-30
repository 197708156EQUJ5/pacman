#include "pacman/Inky.hpp"

#include <iostream>

namespace pacman
{

Inky::Inky(int x, int y, Direction direction, bool isHome) : 
    Ghost(x, y, direction, isHome)
{
}

int Inky::getSrcCol()
{
    int srcCol = -1;

    if (direction == Direction::LEFT)
    {
        srcCol = isOddMove ? InkyConstants::SRC_LEFT_1 : InkyConstants::SRC_LEFT_2;
    }
    else if (direction == Direction::RIGHT)
    {
        srcCol = isOddMove ? InkyConstants::SRC_RIGHT_1 : InkyConstants::SRC_RIGHT_2;
    }
    if (direction == Direction::UP)
    {
        srcCol = isOddMove ? InkyConstants::SRC_UP_1 : InkyConstants::SRC_UP_2;
    }
    else if (direction == Direction::DOWN)
    {
        srcCol = isOddMove ? InkyConstants::SRC_DOWN_1 : InkyConstants::SRC_DOWN_2;
    }

    return srcCol;
}

int Inky::getSrcRow()
{
    return InkyConstants::SRC_ROW;
}

}
