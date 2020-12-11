#pragma once

#include "pacman/Character.hpp"

namespace pacman
{

class Pacman : public Character
{
public:

    Pacman();
    ~Pacman() = default;
    
    int getSrcCol();
    int getSrcRow();
    void move();
    void changeDirection(Direction direction);

    void incrementDotCounter();
    void resetDotCounter();
    int getDotCounter();
    
private:

    int dotCounter;

};

} // namespace pacman

