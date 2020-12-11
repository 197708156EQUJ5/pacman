#include "pacman/FruitTimer.hpp"

#include "pacman/Utils.hpp"

#include <iostream>
#include <ctime>
#include <ratio>

using namespace std::chrono;

namespace pacman
{

FruitTimer::FruitTimer(std::function<void()> removeFruit) :
    isRunning(false),
    isTimerRunning(false),
    delay(0.0),
    removeFruit(removeFruit)
{
}

FruitTimer::~FruitTimer()
{
    this->isRunning = false;
}

void FruitTimer::run()
{
    printf("run()\n");
    this->isRunning = true;

    int transitionIndex = 0;

    while (this->isRunning)
    {
        if (this->isTimerRunning)
        {
            steady_clock::time_point currentTime = steady_clock::now();

            duration<int> timeDelta = duration_cast<duration<int>>(currentTime - this->startTime);
            
            if (timeDelta.count() >= delay)
            {
                this->removeFruit();
                this->isTimerRunning = false;
            }
        }
    }
}

void FruitTimer::pause()
{
    if (this->isTimerRunning)
    {
        this->isTimerRunning = false;
    }
}

void FruitTimer::startTimer()
{
    if (!this->isTimerRunning)
    {
        delay = Util::generateRandom();
        this->startTime = steady_clock::now();
        printf("startTime: %d delay %.2f\n", startTime, delay);
        this->isTimerRunning = true;
    }
}

void FruitTimer::reset()
{
    this->isTimerRunning = false;
    this->startTimer();
}

void FruitTimer::stop()
{
    this->isRunning = false;
}

} // namespace pacman

