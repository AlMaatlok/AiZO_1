#include "QuickSort.h"

#include <chrono>
#include <cstring>
#include <iostream>
#include <fstream>
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
    srand(time(nullptr));
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
    char* time_file = generate_time_results_filename(pivot, size);
    ofstream plik(time_file);
    delete[] time_file;

    for (int i = 0; i < iterations; i++) {
        NumberGenerator<T> number_generator;
        Timer timer;
        Sort<T> sort;

        cout << "Test nr " << i + 1 << endl;
        T* data = new T[size];
        for (int j = 0; j < size; j++) {
            data[j] = number_generator.generate();
        }

        timer.start();
        this->sort(data, 0, size - 1, pivot);
        timer.stop();

        bool is_sorted = sort.is_sorted(data, size);
        if (!is_sorted) {
            cout << "Sorting failed!" << endl;
        } else {
            cout << "Sorting successful!" << endl;
            FileHandler<T> file_handler;
            int time_result = timer.result();
            plik << time_result << endl;
            char* filename = generate_filename(pivot, size);
            file_handler.writeData(filename, size,data);
            delete[] filename;
        }

        delete[] data;
    }
}

template <typename T>
void QuickSort<T>::sorting_file(char* filename, pivotIndex pivot) {
    FileHandler<T> file_handler;
    Timer timer;
    Sort<T> sort;

    int size = file_handler.numberOfValues(filename);
    T* data = file_handler.readData(filename);

    char* time_file = generate_time_results_filename(pivot, size);
    ofstream plik(time_file);
    delete[] time_file;

    timer.start();
    this->sort(data, 0, size - 1, pivot);
    timer.stop();
    bool is_sorted = sort.is_sorted(data, size);
    if (!is_sorted) {
        cout << "Sorting failed!" << endl;
    }
    else {
        cout << "Sorting";
        int time_result = timer.result();
        plik << time_result << endl;

        char* filename_sorted = generate_filename(pivot, size);
        file_handler.writeData(filename_sorted, size, data);
        delete[] filename_sorted;
    }
    delete[] data;
}

template<typename T>
int QuickSort<T>::partition(T *data, int left, int right, pivotIndex pivot) {
    int pivotIndex;

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
char* QuickSort<T>::generate_filename(pivotIndex pivot, int size) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "QuickSort-";

    if (pivot == FIRST)
        filename << "FIRST-";
    else if (pivot == LAST)
        filename << "LAST-";
    else if (pivot == MIDDLE)
        filename << "MIDDLE-";
    else if (pivot == RANDOM)
        filename << "RANDOM-";
    else
        filename << "UNKNOWN-";

    filename << typeid(T).name() << "-"
             << size << "-"
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
char* QuickSort<T>::generate_time_results_filename(pivotIndex pivot, int size) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    std::stringstream filename;
    filename << "Times-QuickSort-";

    if (pivot == FIRST)
        filename << "FIRST-";
    else if (pivot == LAST)
        filename << "LAST-";
    else if (pivot == MIDDLE)
        filename << "MIDDLE-";
    else if (pivot == RANDOM)
        filename << "RANDOM-";
    else
        filename << "UNKNOWN-";

    filename << typeid(T).name() << "-"
             << size << "-"
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