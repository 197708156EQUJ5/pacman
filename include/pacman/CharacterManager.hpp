#pragma once

#include "pacman/Ghost.hpp"
#include "pacman/Pacman.hpp"

#include <memory>

namespace pacman
{

class CharacterManager
{
public:

    CharacterManager();
    ~CharacterManager() = default;

    void initCharacters();
    std::shared_ptr<Pacman> getPacman();

private:

    std::shared_ptr<Pacman> pacman;
    std::shared_ptr<Ghost> blinky;
    std::shared_ptr<Ghost> pinky;
    std::shared_ptr<Ghost> inky;
    std::shared_ptr<Ghost> clyde;

};

}
