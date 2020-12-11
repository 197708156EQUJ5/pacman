#pragma once

#include "pacman/fruit/Fruit.hpp"

namespace pacman
{

class Key : public Fruit
{
public:

    Key();
    ~Key() = default;
    
    int getSrcCol();
    int getSrcRow();
    int getValue();
    
private:

};

} // namespace pacman

