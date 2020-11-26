#include "pacman/CharacterManager.hpp"

namespace pacman
{
    
CharacterManager::CharacterManager()
{
    pacman = std::make_shared<Pacman>();
    blinky = std::make_shared<Ghost>();
    pinky = std::make_shared<Ghost>();
    inky = std::make_shared<Ghost>();
    clyde = std::make_shared<Ghost>();
}

std::shared_ptr<Pacman> CharacterManager::getPacman()
{
    return pacman;
}

}
