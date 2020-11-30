#include "pacman/Pacman.hpp"

#include "pacman/Constants.hpp"
#include <iostream>

namespace pacman
{

Pacman::Pacman() :
    Character(PacmanConstants::START_COL * Constants::CHARACTER_SIZE, 
    //Character(PacmanConstants::START_COL * Constants::CHARACTER_SIZE - (Constants::CHARACTER_SIZE / 2),
            //PacmanConstants::START_ROW * Constants::CHARACTER_SIZE,
            PacmanConstants::START_ROW * Constants::CHARACTER_SIZE - (Constants::CHARACTER_SIZE / 2),
            Direction::NONE)
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

void Pacman::move()
{
    if (direction == Direction::LEFT)
    {
        x -= 4;
    }
    else if (direction == Direction::RIGHT)
    {
        x += 4;
    }
    else if (direction == Direction::DOWN)
    {
        y += 4;
    }
    else if (direction == Direction::UP)
    {
        y -= 4;
    }
    isOddMove = !isOddMove;
}

void Pacman::changeDirection(Direction direction)
{
    this->direction = direction;
}

}
