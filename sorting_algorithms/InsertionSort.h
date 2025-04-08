#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H
#include "Sort.h"



template <typename T>
class InsertionSort: public Sort<T>{
public:
    InsertionSort();
    T* sort(T* data, int size);
    void sorting_file(int iterations, T* data, int size);
    void sorting_test(int iterations, int size);
};


#endif //INSERTIONSORT_H
