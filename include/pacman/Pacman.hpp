#pragma once

#include "pacman/Character.hpp"
#include "pacman/Constants.hpp"

namespace pacman
{

class Pacman : public Character
{
public:

    Pacman(int col = PacmanConstants::START_COL * Constants::CHARACTER_SIZE, 
            int y = PacmanConstants::START_ROW * Constants::CHARACTER_SIZE, 
            Direction direction = Direction::LEFT); 
    ~Pacman() = default;
    
    int getSrcCol();
    int getSrcRow();
    void move();
    
private:

    //static const int 
};

} // namespace pacman

