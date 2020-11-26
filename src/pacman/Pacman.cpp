#include "pacman/Pacman.hpp"

#include "pacman/Constants.hpp"
#include <iostream>

namespace pacman
{

Pacman::Pacman(int x, int y, Direction direction) : 
    Character(x, y, direction)
{
}

int Pacman::getSrcCol()
{
    int srcCol = -1;

    if (direction == Direction::LEFT)
    {
        if (x % 2 == 0)
        {
            srcCol = PacmanConstants::SRC_LEFT_1_COL;
        }
        else
        {
            srcCol = PacmanConstants::SRC_LEFT_2_COL;
        }
    }

    return srcCol;
}

int Pacman::getSrcRow()
{
    int srcRow = -1;

    if (direction == Direction::LEFT)
    {
        srcRow = PacmanConstants::SRC_LEFT_ROW;
    }

    return srcRow;
}

void Pacman::move()
{
    if (direction == Direction::LEFT)
    {
        x--;
    }
}

}
