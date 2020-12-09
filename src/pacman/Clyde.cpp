#include "pacman/Clyde.hpp"

namespace pacman
{

Clyde::Clyde() :
    Ghost(ClydeConstants::START_COL, ClydeConstants::START_ROW, ClydeConstants::SCATTER_COL, ClydeConstants::SCATTER_ROW, Direction::UP, true, false, false)
{
    exitStrategy =
    {
        {Cell{ClydeConstants::START_COL, ClydeConstants::START_ROW}, Direction::LEFT},
        {Cell{PinkyConstants::START_COL, PinkyConstants::START_ROW}, Direction::UP},
        {Cell{BlinkyConstants::START_COL, BlinkyConstants::START_ROW}, Direction::LEFT}
    };
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

int Clyde::getReleaseCounter()
{
    return 10;
    //return 60;
}

bool Clyde::preExitingCheck()
{
    if ((y - ClydeConstants::START_ROW < 0 && direction == Direction::UP || 
            y - ClydeConstants::START_ROW > 0 && direction == Direction::DOWN) && preCheck)
    {
        preCheck = false;
        return true;
    }

    preCheck = false;
    return false;
}

}
