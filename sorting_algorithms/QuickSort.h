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
    T* sorted(T* data, int size, int left, int right, pivotIndex index);
    void sort(T* data, int left, int right, pivotIndex index);
    void sorting_file(int iterations, T* data, int size, pivotIndex index);
    void sorting_test(int iterations, int size, pivotIndex index);


private:
    int partition(T* data, int left, int right, pivotIndex index);
    void swap(T* first, T* second);
};



#endif //QUICKSORT_H
