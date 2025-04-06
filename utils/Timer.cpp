#include "Timer.h"
#include <iostream>

using namespace std;


Timer::Timer() { reset(); }

void Timer::reset() {
    start_time = end_time = high_resolution_clock::now();
}

void Timer::start() {
    start_time = high_resolution_clock::now();
}

void Timer::stop() {
    end_time = high_resolution_clock::now();
}

int Timer::result() {
    auto duration = std::chrono::duration_cast<milliseconds>(end_time - start_time).count();
    return static_cast<int>(duration);;
}
