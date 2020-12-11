#pragma once

#include "pacman/fruit/Fruit.hpp"

namespace pacman
{

class Bell : public Fruit
{
public:

    Bell();
    ~Bell() = default;
    
    int getSrcCol();
    int getSrcRow();
    
private:

};

} // namespace pacman

