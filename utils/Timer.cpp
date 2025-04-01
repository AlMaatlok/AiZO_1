#include "Timer.h"
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
    return static_cast<int>(duration_cast<milliseconds>(end_time - start_time).count());
}
