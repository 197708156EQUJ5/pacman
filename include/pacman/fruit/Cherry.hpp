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
    
private:

};

} // namespace pacman

