#pragma once

#include <chrono>

#include "Namespace.hpp"

SPF_NS_BEGIN

class Timer
{
private:
    std::chrono::high_resolution_clock::time_point _startTime;

public:
    Timer();

    void start();
    double getElapsedTimeInSeconds();
};

SPF_NS_END
