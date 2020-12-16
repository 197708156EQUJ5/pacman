#include "pacman/Timer.hpp"

#include "pacman/Utils.hpp"

#include <iostream>
#include <ctime>
#include <ratio>

using namespace std::chrono;

namespace pacman
{

Timer::Timer(int low, int high, std::function<void()> timerDone, float delay) :
    isRunning(false),
    isTimerRunning(false),
    low(low),
    high(high),
    delay(delay),
    timerDone(timerDone)
{
}

Timer::~Timer()
{
    this->isRunning = false;
}

void Timer::run()
{
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
                this->timerDone();
                this->isTimerRunning = false;
            }
        }
    }
}

void Timer::pause()
{
    if (this->isTimerRunning)
    {
        this->isTimerRunning = false;
    }
}

void Timer::startTimer()
{
    if (!this->isTimerRunning)
    {
        if (!(this->delay > 0.0))
        {
            this->delay = Util::generateRandom(low, high);
        }
        this->startTime = steady_clock::now();
        this->isTimerRunning = true;
    }
}

void Timer::reset()
{
    this->isTimerRunning = false;
    this->startTimer();
}

void Timer::stop()
{
    this->isRunning = false;
}

} // namespace pacman

