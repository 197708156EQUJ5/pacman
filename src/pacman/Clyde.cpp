#include "pacman/Clyde.hpp"

namespace pacman
{

Clyde::Clyde(int x, int y, Direction direction, bool isHome) : 
    Ghost(x, y, direction, isHome)
{
}

int Clyde::getSrcCol()
{
    int srcCol = -1;

    if (direction == Direction::LEFT)
    {
        srcCol = isOddMove ? ClydeConstants::SRC_LEFT_1 : ClydeConstants::SRC_LEFT_2;
    }
    else if (direction == Direction::RIGHT)
    {
        srcCol = isOddMove ? ClydeConstants::SRC_RIGHT_1 : ClydeConstants::SRC_RIGHT_2;
    }
    if (direction == Direction::UP)
    {
        srcCol = isOddMove ? ClydeConstants::SRC_UP_1 : ClydeConstants::SRC_UP_2;
    }
    else if (direction == Direction::DOWN)
    {
        srcCol = isOddMove ? ClydeConstants::SRC_DOWN_1 : ClydeConstants::SRC_DOWN_2;
    }

    return srcCol;
}

int Clyde::getSrcRow()
{
    return ClydeConstants::SRC_ROW;
}

}
