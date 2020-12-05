#pragma once

#include "pacman/AdjacentTile.hpp"
#include "pacman/Blinky.hpp"
#include "pacman/Cell.hpp"
#include "pacman/Clyde.hpp"
#include "pacman/Inky.hpp"
#include "pacman/Pacman.hpp"
#include "pacman/Pinky.hpp"

#include <memory>
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

private:

    std::shared_ptr<Pacman> pacman;
    std::shared_ptr<Ghost> blinky;
    std::shared_ptr<Ghost> pinky;
    std::shared_ptr<Ghost> inky;
    std::shared_ptr<Ghost> clyde;

    std::vector<int> findLegalDirections(std::shared_ptr<Ghost> ghost);
    void printCells(AdjacentTile adjacentTile, std::shared_ptr<Character> character);

};

}
