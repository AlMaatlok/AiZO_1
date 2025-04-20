#ifndef SORT_H
#define SORT_H
#include <string>

using namespace std;
using namespace pmr;

template <typename T>
class Sort {

public:
    Sort();
    bool isSorted(T* data, int size);
    T* sortArrayForTest2(T* data, int size, int argument);
};



#endif //SORT_H
