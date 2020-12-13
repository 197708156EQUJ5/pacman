#include "pacman/Pinky.hpp"

#include <iostream>

namespace pacman
{

Pinky::Pinky() :
    Ghost(PinkyConstants::START_COL, PinkyConstants::START_ROW, PinkyConstants::SCATTER_COL, PinkyConstants::SCATTER_ROW, Direction::UP, true, true, true)
{
    exitStrategy = {
       std::make_pair(Cell{PinkyConstants::START_COL, PinkyConstants::START_ROW}, Direction::UP),
       std::make_pair(Cell{BlinkyConstants::START_COL, BlinkyConstants::START_ROW}, Direction::LEFT)
       };
}

int Pinky::getSrcCol()
{
    int srcCol = -1;

    GhostMode mode = getMode();
    if (mode == GhostMode::SCATTER || mode == GhostMode::CHASE)
    {
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

int Pinky::getSrcRow()
{
    int srcRow = -1;
    GhostMode mode = getMode();
    if (mode == GhostMode::SCATTER || mode == GhostMode::CHASE)
    {
        srcRow = PinkyConstants::SRC_ROW;
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

int Pinky::getReleaseCounter()
{
    return 0;
}

bool Pinky::preExitingCheck()
{
    preCheck = false;
    return false;
}

}
