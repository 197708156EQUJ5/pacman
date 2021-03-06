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

    GhostMode mode = getMode();
    if (mode == GhostMode::SCATTER || mode == GhostMode::CHASE)
    {
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
    }
    else if (mode == GhostMode::EYES)
    {
        if (direction == Direction::LEFT)
        {
            srcCol = isOddMove ? GhostConstants::SRC_EYES_LEFT_1 : GhostConstants::SRC_EYES_LEFT_2;
        }
        else if (direction == Direction::RIGHT)
        {
            srcCol = isOddMove ? GhostConstants::SRC_EYES_RIGHT_1 : GhostConstants::SRC_EYES_RIGHT_2;
        }
        if (direction == Direction::UP)
        {
            srcCol = isOddMove ? GhostConstants::SRC_EYES_UP_1 : GhostConstants::SRC_EYES_UP_2;
        }
        else if (direction == Direction::DOWN)
        {
            srcCol = isOddMove ? GhostConstants::SRC_EYES_DOWN_1 : GhostConstants::SRC_EYES_DOWN_2;
        }
    }
    else if (mode == GhostMode::FRIGHTENED)
    {
        srcCol = isOddMove ? GhostConstants::SRC_FRIGHTENED_COL_1 : GhostConstants::SRC_FRIGHTENED_COL_2;
    }

    return srcCol;
}

int Clyde::getSrcRow()
{
    int srcRow = -1;
    GhostMode mode = getMode();
    if (mode == GhostMode::SCATTER || mode == GhostMode::CHASE)
    {
        srcRow = ClydeConstants::SRC_ROW;
    }
    else if (mode == GhostMode::EYES)
    {
        srcRow = GhostConstants::SRC_EYES_ROW;
    }
    else if (mode == GhostMode::FRIGHTENED)
    {
        srcRow = GhostConstants::SRC_FRIGHTENED_ROW;
    }

    return srcRow;
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
