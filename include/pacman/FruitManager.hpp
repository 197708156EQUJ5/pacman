#pragma once

#include "pacman/Cell.hpp"
#include "pacman/fruit/Cherry.hpp"
#include "pacman/fruit/Fruit.hpp"

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

