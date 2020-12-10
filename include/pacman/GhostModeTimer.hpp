#pragma once

#include "pacman/GhostMode.hpp"

#include <atomic>
#include <chrono>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

namespace pacman
{

class GhostModeTimer
{
public:

    GhostModeTimer(std::vector<std::pair<int, GhostMode>> transitionDelays, std::function<void(GhostMode)> transitionGhostMode);
    ~GhostModeTimer();

    void run();
    void startTimer();
    void pause();
    void reset();
    void stop();

private:

    std::atomic<bool> isRunning;
    std::atomic<bool> isTimerRunning;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::seconds transitionDelay;
    std::function<void(GhostMode)> transitionGhostMode;
    std::vector<std::pair<int, GhostMode>> transitionDelays;

};

} // namespace pacman

