#ifndef SORT_H
#define SORT_H
#include <string>

using namespace std;
using namespace pmr;

template <typename T>
class Sort {

public:
    Sort();
    bool is_sorted(T* data, int size);
    static T* sort_array_for_test2(T* data, int size, float percentage_of_sorting, bool ascending);
};



#endif //SORT_H
