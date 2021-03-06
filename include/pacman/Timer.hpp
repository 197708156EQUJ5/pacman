#pragma once

#include <atomic>
#include <chrono>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

namespace pacman
{

class Timer
{
public:

    Timer(int low = 0, int high = 1, std::function<void()> timerDone = nullptr, float delay = 0.0);
    ~Timer();

    void run();
    void startTimer();
    void pause();
    void reset();
    void stop();

private:

    std::atomic<bool> isRunning;
    std::atomic<bool> isTimerRunning;
    std::chrono::steady_clock::time_point startTime;
    std::function<void()> timerDone;
    int low;
    int high;
    double delay;

};

} // namespace pacman

