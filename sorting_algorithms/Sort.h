#ifndef SORT_H
#define SORT_H
#include <string>

using namespace std;
using namespace pmr;

template <typename T>
class Sort {

public:
    Sort(T* data, int size);
    bool is_sorted(T* data, int size);
    static T* sort_array_for_test2(T* data, int size, float percentage_of_sorting, bool ascending);
    void sorting_from_file(T* data, int size);
    void sorting_test(int iterations, int size);
    char* generate_time_results_filename(char** sorting);

protected:
    T* not_sorted_data;
    T* data;
    int size;
};



#endif //SORT_H
