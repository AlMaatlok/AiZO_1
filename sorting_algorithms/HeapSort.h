#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "Sort.h"

template <typename T>
class HeapSort : public Sort<T> {
public:

    HeapSort();
    T* sort(T* data, int size);
    void sortingFile(char* filename, int distribution);
    void sortingTest(int iterations, int size, int distribution);

private:
    void heapify(T* data, int size, int i);
    char* generateTimeResultsFilename(int size, int distribution);
    char* generateFilename(int size, int distribution, int nr);
};

#endif //HEAPSORT_H
