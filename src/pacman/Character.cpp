#include "pacman/Character.hpp"

namespace pacman
{

Character::Character(int x, int y, Direction direction, bool isOddMove) :
    x(x),
    y(y),
    direction(direction),
    isOddMove(isOddMove)
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
