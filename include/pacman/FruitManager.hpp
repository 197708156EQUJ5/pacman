#pragma once

#include "pacman/Cell.hpp"
#include "pacman/fruit/Apple.hpp"
#include "pacman/fruit/Bell.hpp"
#include "pacman/fruit/Cherry.hpp"
#include "pacman/fruit/Fruit.hpp"
#include "pacman/fruit/Galaxian.hpp"
#include "pacman/fruit/Grape.hpp"
#include "pacman/fruit/Key.hpp"
#include "pacman/fruit/Peach.hpp"
#include "pacman/fruit/Strawberry.hpp"

#include <memory>
#include <vector>

namespace pacman
{

class FruitManager
{

public:

    FruitManager();
    ~FruitManager() = default;
    
    Cell getFruit(int level);

private:
    
    std::vector<std::shared_ptr<Fruit>> fruits;
};

} // namespace pacman

