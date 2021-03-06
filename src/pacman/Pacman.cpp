#include "pacman/Pacman.hpp"

#include "pacman/Constants.hpp"
#include <iostream>

namespace pacman
{

Pacman::Pacman() :
    Character(PacmanConstants::START_COL, PacmanConstants::START_ROW, Direction::NONE),
    isEnergized(false),
    dotCounter(0)
{
}

int Pacman::getSrcCol()
{
    int srcCol = -1;

    if (direction == Direction::NONE)
    {
        srcCol = PacmanConstants::SRC_START_COL;
    }
    else if (direction == Direction::LEFT)
    {
        srcCol = isOddMove ? PacmanConstants::SRC_LEFT_1 : PacmanConstants::SRC_LEFT_2;
    }
    else if (direction == Direction::RIGHT)
    {
        srcCol = isOddMove ? PacmanConstants::SRC_RIGHT_1 : PacmanConstants::SRC_RIGHT_2;
    }
    if (direction == Direction::UP)
    {
        srcCol = isOddMove ? PacmanConstants::SRC_UP_1 : PacmanConstants::SRC_UP_2;
    }
    else if (direction == Direction::DOWN)
    {
        srcCol = isOddMove ? PacmanConstants::SRC_DOWN_1 : PacmanConstants::SRC_DOWN_2;
    }

    return srcCol;
}

int Pacman::getSrcRow()
{
    if (direction == Direction::NONE)
    {
        return PacmanConstants::SRC_START_ROW;
    }

    return PacmanConstants::SRC_ROW;
}

int Pacman::getSpeed(int level)
{
    if (level == 1)
    {
        if (this->isEnergized)
        {
            return 54;
        }
        return 48;
    }

}

void Pacman::move()
{
    if (!collided)
    {
        if (direction == Direction::LEFT)
        {
            x -= Constants::MAXIMUM_PIXEL_SPEED;
        }
        else if (direction == Direction::RIGHT)
        {
            x += Constants::MAXIMUM_PIXEL_SPEED;
        }
        else if (direction == Direction::DOWN)
        {
            y += Constants::MAXIMUM_PIXEL_SPEED;
        }
        else if (direction == Direction::UP)
        {
            y -= Constants::MAXIMUM_PIXEL_SPEED;
        }
    }
    isOddMove = !isOddMove;
}

void Pacman::changeDirection(Direction direction)
{
    this->direction = direction;
}

void Pacman::incrementDotCounter()
{
    this->dotCounter++;
}

void Pacman::resetDotCounter()
{
    this->dotCounter = 0;
}

int Pacman::getDotCounter()
{
    return this->dotCounter;
}

bool Pacman::setEnergized(bool isEnergized)
{
    this->isEnergized = isEnergized;
}

}
