#include "pacman/FruitManager.hpp"

#include <iostream>

namespace pacman
{

FruitManager::FruitManager()
{
    fruits = {std::make_shared<Cherry>()};
}

Cell FruitManager::getFruit(int level)
{
    std::shared_ptr<Fruit> fruit = fruits.at(level);
    return Cell{fruit->getSrcCol(), fruit->getSrcRow()};
}

} // namespace pacman

