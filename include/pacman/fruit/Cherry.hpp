#pragma once

#include "pacman/fruit/Fruit.hpp"

namespace pacman
{

class Cherry : public Fruit
{
public:

    Cherry();
    ~Cherry() = default;
    
    int getSrcCol();
    int getSrcRow();
    int getValue();
    
private:

};

} // namespace pacman

