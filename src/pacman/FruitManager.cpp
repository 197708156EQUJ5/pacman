#include "pacman/FruitManager.hpp"

#include <iostream>

namespace pacman
{

FruitManager::FruitManager()
{
    fruits = {std::make_shared<Cherry>(),
        std::make_shared<Strawberry>(),
        std::make_shared<Peach>(),
        std::make_shared<Peach>(),
        std::make_shared<Apple>(),
        std::make_shared<Apple>(),
        std::make_shared<Grape>(),
        std::make_shared<Grape>(),
        std::make_shared<Galaxian>(),
        std::make_shared<Galaxian>(),
        std::make_shared<Bell>(),
        std::make_shared<Bell>(),
        std::make_shared<Key>(),
        std::make_shared<Key>(),
        std::make_shared<Key>(),
        std::make_shared<Key>(),
        std::make_shared<Key>(),
        std::make_shared<Key>(),
        std::make_shared<Key>(),
        std::make_shared<Key>(),
        std::make_shared<Key>()};
}

Cell FruitManager::getFruit(int level)
{
    std::shared_ptr<Fruit> fruit = fruits.at(level);
    return Cell{fruit->getSrcCol(), fruit->getSrcRow()};
}

} // namespace pacman

