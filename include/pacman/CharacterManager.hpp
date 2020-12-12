#pragma once

#include "pacman/AdjacentTile.hpp"
#include "pacman/Blinky.hpp"
#include "pacman/Cell.hpp"
#include "pacman/Clyde.hpp"
#include "pacman/Inky.hpp"
#include "pacman/Pacman.hpp"
#include "pacman/Pinky.hpp"
#include "pacman/Timer.hpp"

#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace pacman
{

class CharacterManager
{
public:

    CharacterManager();
    ~CharacterManager() = default;

    void initCharacters();
    std::shared_ptr<Pacman> getPacman();
    std::vector<std::shared_ptr<Ghost>> getGhosts();
    bool canMovePacman();
    bool canMoveGhost(std::shared_ptr<Ghost> ghost);
    void incrementDotCounter();
    void updateGhostMode(GhostMode ghostMode);
    void checkCollision();

private:

    std::shared_ptr<Pacman> pacman;
    std::shared_ptr<Ghost> blinky;
    std::shared_ptr<Ghost> pinky;
    std::shared_ptr<Ghost> inky;
    std::shared_ptr<Ghost> clyde;
    std::vector<std::shared_ptr<Ghost>> releaseOrder;
    int releaseOrderIndex;
    std::shared_ptr<std::mutex> mtx;
    std::unique_ptr<Timer> timer;
    std::unique_ptr<std::thread> timerThread;

    std::vector<int> findLegalDirections(AdjacentTile adjacentTile, std::shared_ptr<Ghost> ghost);
    void selectNewDirection(AdjacentTile adjacentTile, std::vector<int> legalDirections, std::shared_ptr<Ghost> ghost);
    void findNextDirection(Cell targetCell, AdjacentTile adjacentTile, std::vector<int> legalDirections, Direction &newDirection);
    void handleChaseMode(std::shared_ptr<Ghost> ghost, AdjacentTile adjacentTile, std::vector<int> legalDirections, Direction &newDirection);

    void determineRelease(std::shared_ptr<Ghost> ghost);
    void freezeCharacters();
    void hideCharacters();
    void hideGhostHandler();
    
};

}
