#pragma once

namespace pacman
{

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Character
{
    
public:

    Character(int x = 0, int y = 0, Direction direction = Direction::LEFT);
    virtual ~Character() {};

    int getX() const;
    int getY() const;
    virtual int getSrcCol() = 0;
    virtual int getSrcRow() = 0;
    //virtual void setX(int x);
    //virtual void setY(int y);
    //virtual void setDirection(Direction &direction);
    
    virtual void move() = 0;
    //virtual void respawn();

protected:

    Direction direction;
    int x;
    int y;

};

} // namespace pacman

