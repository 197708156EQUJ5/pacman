#pragma once

#include "pacman/Character.hpp"

namespace pacman
{

class Fruit : public Character
{
public:

    Fruit(int x = 0, int y = 0, Direction direction = Direction::NONE);
    ~Fruit() = default;
    
    virtual int getSrcCol() {};
    virtual int getSrcRow() {};
    int getSpeed(int level) {};
    virtual int getValue() = 0;
    void move() {};
    void changeDirection(Direction direction) {};
    
private:

};

} // namespace pacman

