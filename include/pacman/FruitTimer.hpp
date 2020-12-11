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

class FruitTimer
{
public:

    FruitTimer(std::function<void()> removeFruit);
    ~FruitTimer();

    void run();
    void startTimer();
    void pause();
    void reset();
    void stop();

private:

    std::atomic<bool> isRunning;
    std::atomic<bool> isTimerRunning;
    std::chrono::steady_clock::time_point startTime;
    std::function<void()> removeFruit;
    double delay;

};

} // namespace pacman

