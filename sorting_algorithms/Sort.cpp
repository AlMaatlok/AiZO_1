#include "Sort.h"

#include <chrono>
//#include <ctime>

using namespace std;
using namespace chrono;

template <typename T>
Sort<T>::Sort() {
}
//method to check if data is fully sorted
template <typename T>
bool Sort<T>::isSorted(T* data, int size) {

    for (int i = 1; i < size; i++) {
        if (data[i - 1] > data[i]) {
            return false;
        }
    }
    return true;
}


//method to sort an array for test number 2
template<typename T>
T* Sort<T>::sortArrayForTest2(T* data, int size, int arg) {

    if (arg == 0 )
        return data;

    bool ascending;
    float sizeOfSortedPart;

    if (arg == -1) {
        ascending = false;
        sizeOfSortedPart = 100;
    }

    else if (arg == 1) {
        ascending = true;
        sizeOfSortedPart = 100;
    }

    else if (arg == 3) {
        ascending = true;
        sizeOfSortedPart = 33;
    }

    else if (arg == 6) {
        ascending = true;
        sizeOfSortedPart = 66;
    }
    else {   //default initial sorting
        ascending = true;
        sizeOfSortedPart = 100;
    }

    for (int i = 0; i < sizeOfSortedPart; i++){
        for (int j = 0; j < sizeOfSortedPart; j++){
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
