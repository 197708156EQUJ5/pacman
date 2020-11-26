#include "pacman/Ghost.hpp"

namespace pacman
{

Ghost::Ghost(int x, int y, Direction direction) : 
    Character(x, y, direction)
{
}

int Ghost::getSrcCol()
{
    int srcCol = -1;

    return srcCol;
}

int Ghost::getSrcRow()
{
    int srcRow = -1;

    return srcRow;
}

void Ghost::move()
{
    if (direction == Direction::LEFT)
    {
        x++;
    }
}

}
