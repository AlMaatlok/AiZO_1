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
    void sort(T* data, int size, gap givenGap);
    T* sorted(T* data, int size, gap givenGap);
    void sorting_file(int iterations, T* data, int size, gap givenGap);
    void sorting_test(int iterations, int size, gap givenGap);
};



#endif //SHELLSORT_H
