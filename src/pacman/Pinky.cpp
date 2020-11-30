#include "pacman/Pinky.hpp"

#include <iostream>

namespace pacman
{

Pinky::Pinky() :
    Ghost(PinkyConstants::START_COL * Constants::CHARACTER_SIZE,
            PinkyConstants::START_ROW * Constants::CHARACTER_SIZE, 
            Direction::DOWN)
{
}

int Pinky::getSrcCol()
{
    int srcCol = -1;

    if (direction == Direction::LEFT)
    {
        srcCol = isOddMove ? PinkyConstants::SRC_LEFT_1 : PinkyConstants::SRC_LEFT_2;
    }
    else if (direction == Direction::RIGHT)
    {
        srcCol = isOddMove ? PinkyConstants::SRC_RIGHT_1 : PinkyConstants::SRC_RIGHT_2;
    }
    if (direction == Direction::UP)
    {
        srcCol = isOddMove ? PinkyConstants::SRC_UP_1 : PinkyConstants::SRC_UP_2;
    }
    else if (direction == Direction::DOWN)
    {
        srcCol = isOddMove ? PinkyConstants::SRC_DOWN_1 : PinkyConstants::SRC_DOWN_2;
    }

    return srcCol;
}

int Pinky::getSrcRow()
{
    return PinkyConstants::SRC_ROW;
}

}
