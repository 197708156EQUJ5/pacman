#pragma once

#include "pacman/fruit/Fruit.hpp"

namespace pacman
{

class Apple : public Fruit
{
public:

    Apple();
    ~Apple() = default;
    
    int getSrcCol();
    int getSrcRow();
    int getValue();
    
private:

};

} // namespace pacman

