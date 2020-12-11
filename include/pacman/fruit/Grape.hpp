#pragma once

#include "pacman/fruit/Fruit.hpp"

namespace pacman
{

class Grape : public Fruit
{
public:

    Grape();
    ~Grape() = default;
    
    int getSrcCol();
    int getSrcRow();
    
private:

};

} // namespace pacman

