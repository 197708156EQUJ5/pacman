#pragma once

#include "pacman/Direction.hpp"

namespace pacman
{

class Character
{
    
public:

    Character(int x = 0, int y = 0, Direction direction = Direction::LEFT, bool isOddMove = false);
    virtual ~Character() {};

    int getX() const;
    int getY() const;
    virtual int getSrcCol() = 0;
    virtual int getSrcRow() = 0;
    virtual void move() = 0;
    virtual void changeDirection(Direction direction) = 0;
    //virtual void respawn();

protected:

    Direction direction;
    int x;
    int y;
    bool isOddMove;

};

} // namespace pacman

