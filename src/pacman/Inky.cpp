#include "pacman/Inky.hpp"

namespace pacman
{

Inky::Inky() :
    Ghost(InkyConstants::START_COL, InkyConstants::START_ROW, InkyConstants::SCATTER_COL, InkyConstants::SCATTER_ROW, Direction::UP, true, false, false)
{
    exitStrategy = 
    {
        {Cell{InkyConstants::START_COL, InkyConstants::START_ROW}, Direction::RIGHT},
        {Cell{PinkyConstants::START_COL, PinkyConstants::START_ROW}, Direction::UP},
        {Cell{BlinkyConstants::START_COL, BlinkyConstants::START_ROW}, Direction::LEFT}
    };
}

int Inky::getSrcCol()
{
    int srcCol = -1;

    GhostMode mode = getMode();
    if (mode == GhostMode::SCATTER || mode == GhostMode::CHASE)
    {
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

int Inky::getSrcRow()
{
    int srcRow = -1;
    GhostMode mode = getMode();
    if (mode == GhostMode::SCATTER || mode == GhostMode::CHASE)
    {
        srcRow = InkyConstants::SRC_ROW;
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

int Inky::getReleaseCounter()
{
    return 10;
    //return 30;
}

bool Inky::preExitingCheck()
{
    if ((y - InkyConstants::START_ROW < 0 && direction == Direction::UP || 
            y - InkyConstants::START_ROW > 0 && direction == Direction::DOWN) && preCheck)
    {
        preCheck = false;
        return true;
    }

    preCheck = false;
    return false;
}

}
