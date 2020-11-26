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

    Character(int col = 0, int row = 0, Direction direction = Direction::LEFT);
    virtual ~Character() {};

    int getCol() const;
    int getRow() const;
    //virtual void setX(int x);
    //virtual void setY(int y);
    //virtual void setDirection(Direction &direction);
    //virtual void move();
    //virtual void respawn();

private:

    int col;
    int row;
    Direction direction;
};

} // namespace pacman

