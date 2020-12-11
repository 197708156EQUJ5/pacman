#pragma once

#include "pacman/fruit/Fruit.hpp"

namespace pacman
{

class Strawberry : public Fruit
{
public:

    Strawberry();
    ~Strawberry() = default;
    
    int getSrcCol();
    int getSrcRow();
    int getValue();
    
private:

};

} // namespace pacman

