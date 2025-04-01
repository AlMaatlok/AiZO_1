#ifndef TIMER_H
#define TIMER_H

#include <chrono>
using namespace std::chrono;

class Timer {
public:
    Timer();
    void reset();
    void start();
    void stop();
    int result();

    private:
    high_resolution_clock::time_point start_time, end_time;
};



#endif //TIMER_H
