#pragma once

#include "pacman/fruit/Fruit.hpp"

namespace pacman
{

class Galaxian : public Fruit
{
public:

    Galaxian();
    ~Galaxian() = default;
    
    int getSrcCol();
    int getSrcRow();
    int getValue();
    
private:

};

} // namespace pacman

