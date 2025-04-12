#include "QuickSort.h"

#include <chrono>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <sstream>
#include <random>
#include "../utils/Timer.h"
#include "../utils/FileHandler.h"
#include "../utils/NumberGenerator.h"
#include "Sort.h"

using namespace std;
using namespace chrono;

template<typename T>
QuickSort<T>::QuickSort() {
}

template <typename T>
T* QuickSort<T>::sort(T* data, int left, int right, pivotIndex pivotInd) {
    if (left < right) {
        int pivot = partition(data, left, right, pivotInd);
        sort(data, left, pivot - 1, pivotInd);
        sort(data, pivot + 1, right, pivotInd);
    }
    return data;
}
template <typename T>
void QuickSort<T>::sorting_test(int iterations, int size, pivotIndex pivot) {
    char* time_file = generate_time_results_filename();
    ofstream plik(time_file);

    for (int i = 0; i < iterations; i++) {
        FileHandler<T> file_handler;
        NumberGenerator<T> number_generator;
        Timer timer;
        Sort<T> sort;

        cout << "Test nr " << i + 1 << endl;
        T* data = new T[size];
        for (int j = 0; j < size; j++) {
            data[j] = number_generator.generate();
        }

        timer.start();
        T* sorted_data = this->sort(data, 0, size - 1, pivot);
        timer.stop();

        bool is_sorted = sort.is_sorted(sorted_data, size);
        if (!is_sorted) {
            cout << "Sorting failed!" << endl;
        } else {
            int time_result = timer.result();
            plik << time_result << endl;
            char* filename = generate_filename();
            file_handler.writeData(filename, size, sorted_data);
        }

        delete[] data;
    }

    delete[] time_file;
}

template <typename T>
void QuickSort<T>::sorting_file(char* filename, pivotIndex pivot) {
    FileHandler<T> file_handler;
    Timer timer;
    Sort<T> sort;

    char* time_file = generate_time_results_filename();
    ofstream plik(time_file);

    int size = file_handler.numberOfValues(filename);
    T* data = file_handler.readData(filename);

    timer.start();
    T* sorted_data = this->sort(data, 0, size - 1, pivot);
    timer.stop();
    bool is_sorted = sort.is_sorted(sorted_data, size);
    if (!is_sorted) {
        cout << "Sorting failed!" << endl;
    }
    else {
        cout << "Posortowane";
        int time_result = timer.result();
        plik << time_result << endl;
        char* filename_sorted = generate_filename();
        file_handler.writeData(filename_sorted, size, sorted_data);
    }
    delete[] data;
    delete[] time_file;
}
template<typename T>
int QuickSort<T>::partition(T *data, int left, int right, pivotIndex pivot) {
    int pivotIndex;
    srand(time(NULL));
    if (pivot == FIRST) {
        pivotIndex = left;
    } else if (pivot == LAST) {
        pivotIndex = right;
    } else if (pivot == MIDDLE) {
        pivotIndex = left + (right - left) / 2;
    } else if (pivot == RANDOM) {
        pivotIndex = left + (rand() % (right - left + 1));
    } else {
        pivotIndex = right;
    }

    swap(&data[pivotIndex], &data[right]);
    T pivotValue = data[right];

    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (data[j] <= pivotValue) {
            i++;
            swap(&data[i], &data[j]);
        }
    }
    swap(&data[i + 1], &data[right]);
    return i + 1;

}
template<typename T>
void QuickSort<T>::swap(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
char* QuickSort<T>::generate_filename() {
    const auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "QuickSort-"
             << typeid(T).name() << "-"
             << (timeInfo->tm_year + 1900) << "-"
             << (timeInfo->tm_mon + 1) << "-"
             << (timeInfo->tm_mday) << "-"
             << (timeInfo->tm_hour) << "."
             << (timeInfo->tm_min) << "."
             << (timeInfo->tm_sec) << ".txt";

    std::string s = filename.str();
    char* result = new char[s.length() + 1];
    strcpy(result, s.c_str());

    return result;
}
template <typename T>
char* QuickSort<T>::generate_time_results_filename() {
    const auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "Times-QuickSort-"
             << typeid(T).name() << "-"
             << (timeInfo->tm_year + 1900) << "-"
             << (timeInfo->tm_mon + 1) << "-"
             << (timeInfo->tm_mday) << "-"
             << (timeInfo->tm_hour) << "."
             << (timeInfo->tm_min) << "."
             << (timeInfo->tm_sec) << ".csv";

    std::string s = filename.str();
    char* result = new char[s.length() + 1];
    strcpy(result, s.c_str());

    return result;
}

template class QuickSort<int>;
template class QuickSort<float>;
template class QuickSort<double>;