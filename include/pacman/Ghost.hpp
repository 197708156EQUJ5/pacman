#pragma once

#include "pacman/Character.hpp"

namespace pacman
{

class Ghost : public Character
{
public:

    Ghost(int x = 0, int y = 0, Direction direction = Direction::LEFT, bool isHome = false, 
            bool isCounterActive = false);
    ~Ghost() = default;
    
    virtual int getSrcCol() {};
    virtual int getSrcRow() {};
    void move();
    void changeDirection(Direction direction);
    bool isHome();
    void resetPelletCounter();
    void increasePelletCounter();
    void setPelletCounterActive();

protected:
    
    bool isGhostHome;
    int pelletCounter;
    bool isCounterActive;
};

} // namespace pacman

