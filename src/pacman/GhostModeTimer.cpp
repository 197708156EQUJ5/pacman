#include "pacman/GhostModeTimer.hpp"

#include "pacman/Utils.hpp"

#include <iostream>

namespace pacman
{

GhostModeTimer::GhostModeTimer(std::vector<std::pair<std::chrono::seconds, GhostMode>> transitionDelays, 
        std::function<void(GhostMode)> transitionGhostMode) :
    isRunning(false),
    transitionDelays(transitionDelays),
    transitionGhostMode(transitionGhostMode)
{
}

void GhostModeTimer::run()
{
    printf("run()\n");
    this->isRunning = true;

    std::chrono::seconds currentTime;
    int transitionIndex = 0;

    while (this->isRunning)
    {
        if (this->isTimerRunning)
        {
            currentTime = Util::chronoTime<std::chrono::seconds>();

            std::chrono::seconds delay = currentTime - this->startTime;
            
            std::pair<std::chrono::seconds, GhostMode> transitionPair = this->transitionDelays.at(transitionIndex);
            std::chrono::seconds transitionDelay = transitionPair.first;
            printf("delay %d transition Delay%d\n", delay.count(), transitionDelay.count());
            if (delay >= transitionDelay)
            {
                GhostMode ghostMode = transitionPair.second;
                this->transitionGhostMode(ghostMode);
                transitionIndex++;
                if (transitionIndex < transitionDelays.size())
                {
                    this->isRunning = false;
                }
            }
        }
    }
}

void GhostModeTimer::pause()
{
    if (this->isTimerRunning)
    {
        this->isTimerRunning = false;
    }
}

void GhostModeTimer::startTimer()
{
    if (!this->isTimerRunning)
    {
        this->startTime = Util::chronoTime<std::chrono::seconds>();
        this->isTimerRunning = true;
    }
}

void GhostModeTimer::reset()
{
    this->isTimerRunning = false;
    this->startTimer();
}

void GhostModeTimer::stop()
{
    this->isRunning = false;
}

} // namespace pacman

