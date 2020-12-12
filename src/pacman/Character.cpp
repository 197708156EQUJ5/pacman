#include "pacman/Character.hpp"

namespace pacman
{

Character::Character(int x, int y, Direction direction) :
    x(x),
    y(y),
    direction(direction),
    isOddMove(false),
    collided(false),
    hidden(false)
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

bool Character::hasCollided()
{
    return collided;
}

void Character::setCollided(bool hasCollided)
{
    collided = hasCollided;
}

bool Character::isHidden()
{
    return this->hidden;
}

void Character::hide(bool hide)
{
    this->hidden = hide;
}

}
