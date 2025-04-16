#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "Sort.h"

template <typename T>
class HeapSort : public Sort<T> {
public:

    HeapSort();
    T* sort(T* data, int size);
    void sorting_file(char* filename, int distribution);
    void sorting_test(int iterations, int size, int distribution);

private:
    void heapify(T* data, int size, int i);
    char* generate_time_results_filename(int size, int distribution);
    char* generate_filename(int size, int distribution);
};

#endif //HEAPSORT_H
