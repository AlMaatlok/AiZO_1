#include "Sort.h"
#include <chrono>
#include <algorithm> // For std::sort

using namespace std;
using namespace chrono;

template <typename T>
Sort<T>::Sort() {
}

// Method to check if data is fully sorted
template <typename T>
bool Sort<T>::isSorted(T* data, int size) {
    for (int i = 1; i < size; i++) {
        if (data[i - 1] > data[i]) {
            return false;
        }
    }
    return true;
}

// Method to sort an array for test number 2
template<typename T>
T* Sort<T>::sortArrayForTest2(T* data, int size, int arg) {
    if (arg == 0) {
        return data; // Not sorted
    }

    bool ascending;
    float sizeOfSortedPart;

    switch (arg) {
        case -1:
            ascending = false;
        sizeOfSortedPart = 100;
        break;

        case 1:
            ascending = true;
        sizeOfSortedPart = 100;
        break;

        case 3:
            ascending = true;
        sizeOfSortedPart = 33;
        break;

        case 6:
            ascending = true;
        sizeOfSortedPart = 66;
        break;

        default:
            ascending = true;
        sizeOfSortedPart = 100;
        break;
    }

    int sortedSize = static_cast<int>(size * (sizeOfSortedPart / 100.0));

    if (ascending) {
        sort(data, data + sortedSize);
    } else {
        sort(data, data + sortedSize, std::greater<T>());
    }

    return data;
}

template class Sort<int>;
template class Sort<float>;
template class Sort<double>;
