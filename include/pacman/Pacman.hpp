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
    int getSpeed(int level);
    void move();
    void changeDirection(Direction direction);

    void incrementDotCounter();
    void resetDotCounter();
    int getDotCounter();
    bool setEnergized(bool isEnergized = true);
    
private:

    int dotCounter;
    bool isEnergized;

};

} // namespace pacman

