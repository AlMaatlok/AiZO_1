#ifndef SHELLSORT_H
#define SHELLSORT_H
#include "Sort.h"



template <typename T>
class ShellSort : public Sort<T> {
public:

    enum gap {
        SHELL,
        HIBBARD
    };

    ShellSort();
    T* sort(T* data, int size, int* gaps, int gapCount);
    void sorting_file(char* filename, gap givenGap, int distribution);
    void sorting_test(int iterations, int size, gap givenGap, int distribution);
private:
    char* generate_time_results_filename(gap givenGap, int size, int distribution);
    char* generate_filename(gap givenGap, int size, int distribution);
    int* generate_gaps(int size, gap givenGap, int* count);

};



#endif //SHELLSORT_H
