#pragma once

#include "pacman/Pinky.hpp"
#include "pacman/Inky.hpp"
#include "pacman/Blinky.hpp"
#include "pacman/Clyde.hpp"
#include "pacman/Pacman.hpp"

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

private:

    std::shared_ptr<Pacman> pacman;
    std::shared_ptr<Ghost> blinky;
    std::shared_ptr<Ghost> pinky;
    std::shared_ptr<Ghost> inky;
    std::shared_ptr<Ghost> clyde;

};

}
