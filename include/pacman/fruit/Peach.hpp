#pragma once

#include "pacman/fruit/Fruit.hpp"

namespace pacman
{

class Peach : public Fruit
{
public:

    Peach();
    ~Peach() = default;
    
    int getSrcCol();
    int getSrcRow();
    
private:

};

} // namespace pacman

