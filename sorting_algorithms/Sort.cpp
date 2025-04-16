#include "Sort.h"

#include <chrono>
//#include <ctime>

using namespace std;
using namespace chrono;

template <typename T>
Sort<T>::Sort() {
}
//Function to check if data is fully sorted
template <typename T>
bool Sort<T>::is_sorted(T* data, int size) {

    for (int i = 1; i < size; i++) {
        if (data[i - 1] > data[i]) {
            return false;
        }
    }
    return true;
}


//Function to sort an array for test number 2
template<typename T>
T* Sort<T>::sort_array_for_test2(T* data, int size, int arg) {

    if (arg == 0 )
        return data;

    bool ascending;
    float size_of_sorted_part;

    if (arg == -1) {
        ascending = false;
        size_of_sorted_part = 100;
    }

    else if (arg == 1) {
        ascending = true;
        size_of_sorted_part = 100;
    }

    else if (arg == 3) {
        ascending = true;
        size_of_sorted_part = 33;
    }

    else if (arg == 6) {
        ascending = true;
        size_of_sorted_part = 66;
    }
    else {   //default initial sorting
        ascending = true;
        size_of_sorted_part = 100;
    }

    for (int i = 0; i < size_of_sorted_part; i++){
        for (int j = 0; j < size_of_sorted_part; j++){
            if ((ascending && data[j] > data[j + 1]) || (!ascending && data[j] < data[j + 1]))
            {
                T temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
    return data;
}



template class Sort<int>;
template class Sort<float>;
template class Sort<double>;
