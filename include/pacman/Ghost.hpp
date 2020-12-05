#pragma once

#include "pacman/Character.hpp"

#include <queue>

namespace pacman
{

class Ghost : public Character
{
public:

    Ghost(int x = 0, int y = 0, Direction direction = Direction::LEFT, bool isHome = false, 
            bool isExiting = false, bool isCounterActive = false);
    ~Ghost() = default;
    
    virtual int getSrcCol() {};
    virtual int getSrcRow() {};
    void move();
    void changeDirection(Direction direction);
    bool isHome();
    void setHome(bool isHome = false);
    bool isExiting();
    void resetPelletCounter();
    void increasePelletCounter();
    void setPelletCounterActive();
    void setCurrentTile(Cell tile);
    Cell getCurrentTile();

    /// Adds direction to the queue.
    /// @param direction the direction to add to the queue.
    void addNextDirection(Direction direction);

    /// Gets the next Direction on the queue.
    /// @return the next direction.
    Direction getNextDirection();
    
    /// @return true if current tile is different from previous tile.
    bool hasTileChanged();
    
    Direction peekNextDirection();
    std::queue<Direction> getQueue();

protected:
    
    bool isGhostHome;
    bool isExitingHome;
    int pelletCounter;
    bool isCounterActive;
    std::queue<Direction> directionQueue;
    Cell currentTile;
    Cell previousTile;
};

} // namespace pacman

