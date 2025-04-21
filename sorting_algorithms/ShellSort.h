#ifndef SHELLSORT_H
#define SHELLSORT_H
#include "Sort.h"



template <typename T>
class ShellSort : public Sort<T> {
public:

    enum gap {
        SHELL,
        HIBBARD
    };

    ShellSort();
    T* sort(T* data, int size, int* gaps, int gapCount);
    void sortingFile(char* filename, gap givenGap, int distribution);
    void sortingTest(int iterations, int size, gap givenGap, int distribution);
private:
    char* generateTimeResultsFilename(gap givenGap, int size, int distribution);
    char* generateFilename(gap givenGap, int size, int distribution, int nr);
    int* generateGaps(int size, gap givenGap, int* count);

};



#endif //SHELLSORT_H
