#pragma once

#include "pacman/Character.hpp"
#include "pacman/GhostMode.hpp"

#include <queue>
#include <utility>

namespace pacman
{

class Ghost : public Character
{
public:

    Ghost(int x = 0, int y = 0, int xTarget = 0, int yTarget = 0, Direction direction = Direction::LEFT, bool isHome = false, 
            bool isExiting = false, bool isCounterActive = false);
    ~Ghost() = default;
    
    virtual int getSrcCol() {};
    virtual int getSrcRow() {};
    void move();
    void changeDirection(Direction direction);
    bool isHome();
    void setHome(bool isHome = true);
    bool isExiting();
    void setExiting(bool isExiting = true);
    
    void resetDotCounter();
    void increaseDotCounter();
    void setDotCounterActive(bool isActive = true);
    bool isDotCounterActive();
    int getDotCounter();
    virtual int getReleaseCounter() = 0;

    void setCurrentTile(Cell tile);
    Cell getCurrentTile();
    void setMode(GhostMode mode);
    GhostMode getMode();
    Cell getTarget();

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

    std::pair<Cell, Direction> peekNextExitStep();
    void advanceNextExitStep();

protected:
    
    bool isGhostHome;
    bool isExitingHome;
    int dotCounter;
    bool isCounterActive;
    std::queue<Direction> directionQueue;
    std::vector<std::pair<Cell, Direction>> exitStrategy;
    int exitStrategyIndex;
    Cell currentTile;
    Cell previousTile;
    int xTarget;
    int yTarget;

private:
    GhostMode ghostMode;

};

} // namespace pacman

