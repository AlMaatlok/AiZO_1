#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H
#include "Sort.h"



template <typename T>
class InsertionSort: public Sort<T>{
public:
    InsertionSort();
    T* sort(T* data, int size);
    void sortingFile(char* filename, int distribution);
    void sortingTest(int iterations, int size, int distribution);

private:
    char* generateTimeResultsFilename(int size, int distribution);
    char* generateFilename(int size, int distribution, int nr);
};


#endif //INSERTIONSORT_H
