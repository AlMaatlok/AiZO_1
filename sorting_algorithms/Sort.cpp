#include "Sort.h"

#include <chrono>
#include <ctime>
#include <iosfwd>
#include <string.h>
#include <ctime>
#include <sstream>
#include <string>
#include <typeinfo>
#include <chrono>

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
T* Sort<T>::sort_array_for_test2(T* data, int size, float percentage_of_sorting, bool ascending) {

    float size_of_sorted_array = static_cast<float>(size) * percentage_of_sorting;

    for (int i = 0; i < size_of_sorted_array; i++){
        for (int j = 0; j < size - 1; j++){
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
