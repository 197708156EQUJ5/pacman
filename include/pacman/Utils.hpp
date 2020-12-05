#pragma once

#include "AdjacentTile.hpp"
#include "Cell.hpp"
#include "Direction.hpp"
#include "Ghost.hpp"

#include <iostream>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

namespace pacman
{

namespace Util
{

SDL_Surface *load_bmp(char const *path);

Direction getOpposite(Direction direction);

Cell convertToGrid(const Cell& cell);

Cell getCenter(Cell cell);

Cell getCenter(int x, const int y);

AdjacentTile getAdjacentTiles(int x, int y, Direction direction);

Cell getCurrentCell(int x, int y);

template<typename T>
void displayTiles(AdjacentTile adjacentTile, std::shared_ptr<Ghost> ghost)
{
    if (typeid(*ghost) == typeid(T))
    {
        Cell ghostCenterTile = getCenter(ghost->getCurrentTile());
        bool currNorth = adjacentTile.north == ghostCenterTile;
        bool currEast = adjacentTile.east == ghostCenterTile;
        bool currSouth = adjacentTile.south == ghostCenterTile;
        bool currWest = adjacentTile.west == ghostCenterTile;
        printf("%s **** AdjacentTiles ****\n", typeid(T).name());
        printf("========================================\n");
        printf("|            |%s %3d, %3d  |            |\n", currNorth ? "X" : " ", adjacentTile.north.col, adjacentTile.north.row);
        printf("|------------|------------|------------|\n");
        printf("|%s %3d, %3d  |            |%s %3d, %3d  |\n", currWest ? "X" : " ", adjacentTile.west.col, adjacentTile.west.row, currEast ? "X" : " ", adjacentTile.east.col, adjacentTile.east.row);
        printf("|------------|------------|------------|\n");
        printf("|            |%s %3d, %3d  |            |\n", currSouth ? "X" : " ", adjacentTile.south.col, adjacentTile.south.row);
        printf("========================================\n");
    }
}

template<typename T>
void displayGhost(std::shared_ptr<Ghost> ghost)
{
    if (typeid(*ghost) == typeid(T))
    {
        printf("%s **** Ghost Details ****\n", typeid(T).name());
        std::string directionStr;
        Direction direction = ghost->getDirection();
        if (direction == Direction::UP)
        {
            directionStr = "UP";
        }
        else if (direction == Direction::DOWN)
        {
            directionStr = "DOWN";
        }
        else if (direction == Direction::LEFT)
        {
            directionStr = "LEFT";
        }
        else if (direction == Direction::RIGHT)
        {
            directionStr = "RIGHT";
        }
        printf("(%3d, %3d) Direction: %s\n", ghost->getX(), ghost->getY(), directionStr.c_str());
    }

}

}
}
