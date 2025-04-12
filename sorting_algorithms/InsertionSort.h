#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H
#include "Sort.h"



template <typename T>
class InsertionSort: public Sort<T>{
public:
    InsertionSort();
    T* sort(T* data, int size);
    void sorting_file(char* filename);
    void sorting_test(int iterations, int size);

private:
    char* generate_time_results_filename(int size);
    char* generate_filename(int size);
};


#endif //INSERTIONSORT_H
