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

std::shared_ptr<Fruit> FruitManager::getFruit(int level)
{
    return fruits.at(level);
}

} // namespace pacman

