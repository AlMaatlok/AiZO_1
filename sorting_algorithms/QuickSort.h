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
    void sortingFile(char* filename, pivotIndex pivot, int distribution);
    void sortingTest(int iterations, int size, pivotIndex pivot, int distribution);

private:
    int partition(T* data, int left, int right, pivotIndex pivot);
    char* generateTimeResultsFilename(pivotIndex pivot, int size, int distribution);
    char* generateFilename(pivotIndex pivot, int size, int distribution, int nr);
    void swap(T* a, T* b);
};



#endif //QUICKSORT_H
