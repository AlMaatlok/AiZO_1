#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "Sort.h"

template <typename T>
class HeapSort : public Sort<T> {
public:

    HeapSort();
    T* sort(T* data, int size);
    void sorting_file(char* filename);
    void sorting_test(int iterations, int size);

private:
    void heapify(T* data, int size, int i);
    char* generate_time_results_filename();
    char* generate_filename();
};

#endif //HEAPSORT_H
