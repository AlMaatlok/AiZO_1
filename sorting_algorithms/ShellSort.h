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
    T* sort(T* data, int size, gap givenGap);
    void sorting_file(char* filename, gap givenGap);
    void sorting_test(int iterations, int size, gap givenGap);
private:
    char* generate_time_results_filename(gap givenGap, int size);
    char* generate_filename(gap givenGap, int size);

};



#endif //SHELLSORT_H
