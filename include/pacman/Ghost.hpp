#pragma once

#include "pacman/Character.hpp"

namespace pacman
{

class Ghost : public Character
{
public:

    Ghost(int x = 0, int y = 0, Direction direction = Direction::LEFT, bool isHome = false);
    ~Ghost() = default;
    
    virtual int getSrcCol() {};
    virtual int getSrcRow() {};
    void move();
    void changeDirection(Direction direction);
    bool isHome();
    void resetPelletCounter();

protected:
    
    bool isGhostHome;
    int pelletCounter;
    bool isPelletCounterActive;
};

} // namespace pacman

