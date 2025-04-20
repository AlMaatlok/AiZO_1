#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H
#include "Sort.h"



template <typename T>
class InsertionSort: public Sort<T>{
public:
    InsertionSort();
    T* sort(T* data, int size);
    void sorting_file(char* filename, int distribution);
    void sorting_test(int iterations, int size, int distribution);

private:
    char* generate_time_results_filename(int size, int distribution);
    char* generate_filename(int size, int distribution, int nr);
};


#endif //INSERTIONSORT_H
