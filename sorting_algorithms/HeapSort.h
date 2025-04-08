#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "Sort.h"

template <typename T>
class HeapSort : public Sort<T> {
public:

    HeapSort();
    void sort(T* data, int size);
    T* sorted(T* data, int size);
    void sorting_file(int iterations, T* data, int size);
    void sorting_test(int iterations, int size);

private:
    void heapify(T* data, int size, int i);
};

#endif //HEAPSORT_H
