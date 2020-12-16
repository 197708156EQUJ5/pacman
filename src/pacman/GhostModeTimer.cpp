#include "pacman/GhostModeTimer.hpp"

#include "pacman/Utils.hpp"

#include <iostream>
#include <ctime>
#include <ratio>

using namespace std::chrono;
using namespace std;

namespace pacman
{

GhostModeTimer::GhostModeTimer(vector<pair<int, GhostMode>> transitionDelays, 
        function<void(GhostMode)> transitionGhostMode) :
    isRunning(false),
    isTimerRunning(false),
    transitionIndex(0),
    transitionDelays(transitionDelays),
    transitionGhostMode(transitionGhostMode)
{
}

GhostModeTimer::~GhostModeTimer()
{
    this->isRunning = false;
}

void GhostModeTimer::run()
{
    this->isRunning = true;


    while (this->isRunning)
    {
        if (this->isTimerRunning)
        {
            steady_clock::time_point currentTime = steady_clock::now();

            duration<int> timeDelta = duration_cast<duration<int>>((currentTime - this->startTime) - (pauseEndTime - pauseStartTime));
            
            pair<int, GhostMode> transitionPair = this->transitionDelays.at(transitionIndex);
            int transitionDelay = transitionPair.first;
            //printf("delay %d transition Delay %d\n", timeDelta.count(), transitionDelay);
            if (timeDelta.count() >= transitionDelay)
            {
                GhostMode nextGhostMode = transitionPair.second;
                this->transitionGhostMode(nextGhostMode);
                transitionIndex++;
                this->startTime = steady_clock::now();
                if (transitionIndex == transitionDelays.size())
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
        printf("pause begins\n");
        this->isTimerRunning = false;
        this->pauseStartTime = steady_clock::now();
    }
    else
    {
        printf("pause ends\n");
        this->isTimerRunning = true;
        this->pauseEndTime = steady_clock::now();
        pair<int, GhostMode> transitionPair = this->transitionDelays.at(transitionIndex);
        this->transitionGhostMode(transitionPair.second);
    }
}

void GhostModeTimer::startTimer()
{
    if (!this->isTimerRunning)
    {
        this->startTime = steady_clock::now();
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

