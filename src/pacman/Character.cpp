#include "pacman/Character.hpp"

namespace pacman
{

Character::Character(int x, int y, Direction direction) :
    x(x),
    y(y),
    direction(direction),
    isOddMove(false)
{
}

int Character::getY() const
{
    return y;
}

int Character::getX() const
{
    return x;
}

Direction Character::getDirection()
{
    return direction;
}

}
