#include "pacman/Character.hpp"

namespace pacman
{

Character::Character(int col, int row, Direction direction) :
    col(col),
    row(row),
    direction(direction)
{
}

int Character::getRow() const
{
    return col;
}

int Character::getCol() const
{
    return row;
}

}
