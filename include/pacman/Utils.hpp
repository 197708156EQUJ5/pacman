#pragma once

#include "AdjacentTile.hpp"
#include "Cell.hpp"
#include "Direction.hpp"
#include "Ghost.hpp"
#include "Pacman.hpp"

#include <chrono>
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

Cell getTileAhead(int x, int y, Direction direction, int tilesAhead);

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
        printf("|%s %3d, %3d  |            |%s %3d, %3d  |\n", currWest ? "X" : " ", 
                adjacentTile.west.col, adjacentTile.west.row, currEast ? "X" : " ", adjacentTile.east.col, adjacentTile.east.row);
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
        std::string directionStr;
        std::string nextDirectionStr;
        Direction direction = ghost->getDirection();
        Direction peekDirection = ghost->peekNextDirection();
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
        else if (direction == Direction::NONE)
        {
            directionStr = "NONE";
        }

        if (peekDirection == Direction::UP)
        {
            nextDirectionStr = "UP";
        }
        else if (peekDirection == Direction::DOWN)
        {
            nextDirectionStr = "DOWN";
        }
        else if (peekDirection == Direction::LEFT)
        {
            nextDirectionStr = "LEFT";
        }
        else if (peekDirection == Direction::RIGHT)
        {
            nextDirectionStr = "RIGHT";
        }
        else if (peekDirection == Direction::NONE)
        {
            nextDirectionStr = "NONE";
        }
        printf("========> %s (%3d, %3d) exiting? %s Direction: %s Next: %s:%d \n", typeid(T).name(), ghost->getX(), ghost->getY(), 
                ghost->isExiting() ? "YES" : "NO", directionStr.c_str(), nextDirectionStr.c_str(), peekDirection);
    }

}

template<typename T>
AdjacentTile getAdjacentTiles(int x, int y, Direction direction)
{
    if (typeid(T) == typeid(Ghost))
    {
        if (direction == Direction::LEFT)
        {
            x -= Constants::TILE_SIZE;
        }
        else if (direction == Direction::RIGHT)
        {
            x += Constants::TILE_SIZE;
        }
        else if (direction == Direction::UP)
        {
            y -= Constants::TILE_SIZE;
        }
        else if (direction == Direction::DOWN)
        {
            y += Constants::TILE_SIZE;
        }
    }
    else if (typeid(T) == typeid(Pacman))
    {
        if (direction == Direction::LEFT)
        {
            x += (Constants::TILE_SIZE / 2 - 1);
        }
        else if (direction == Direction::RIGHT)
        {
            x -= (Constants::TILE_SIZE / 2 - 1);
        }
        else if (direction == Direction::UP)
        {
            y += (Constants::TILE_SIZE / 2 - 1);
        }
        else if (direction == Direction::DOWN)
        {
            y -= (Constants::TILE_SIZE / 2 - 1);
        }
    }

    const Cell north{Util::getCenter(x, y - Constants::TILE_SIZE)};
    const Cell south{Util::getCenter(x, y + Constants::TILE_SIZE)};
    const Cell east{Util::getCenter(x + Constants::TILE_SIZE, y)};
    const Cell west{Util::getCenter(x - Constants::TILE_SIZE, y)};
   
    return {north, west, south, east};
}

template<typename T>
static T chronoTime(void)
{
    return std::chrono::duration_cast<T>(std::chrono::system_clock::now().time_since_epoch());
}

float distance(int x1, int x2, int y1, int y2);

float generateRandom(int low, int high);

}
}
