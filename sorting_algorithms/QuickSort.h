#ifndef QUICKSORT_H
#define QUICKSORT_H



#include "Sort.h"


template <typename T>
class QuickSort : public Sort<T> {
public:
    enum pivotIndex {
        FIRST,
        LAST,
        MIDDLE,
        RANDOM
    };

    QuickSort();
    T* sort(T* data, int left, int right, pivotIndex pivot);
    void sorting_file(char* filename, pivotIndex pivot);
    void sorting_test(int iterations, int size, pivotIndex pivot);

private:
    int partition(T* data, int left, int right, pivotIndex pivot);
    char* generate_time_results_filename(pivotIndex pivot);
    char* generate_filename(pivotIndex pivot);
    void swap(T* a, T* b);
};



#endif //QUICKSORT_H
