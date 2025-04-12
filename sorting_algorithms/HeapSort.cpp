#include "HeapSort.h"
#include "../utils/FileHandler.h"
#include "../utils/NumberGenerator.h"
#include "../utils/Timer.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;
using namespace chrono;

template<typename T>
HeapSort<T>::HeapSort() {}

template<typename T>
T* HeapSort<T>::sort(T *data, int size) {
    // Build max-heap
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(data, size, i);

    // Extracting element from the heap
    for (int i = size - 1; i >= 0; i--) {
        // Moving the current root to the last element of the array.
        T temp = data[i];
        data[i] = data[0];
        data[0] = temp;

        // Calling max heapify on the shrink heap
        heapify(data, i, 0);
    }
    return data;
}

template<typename T>
void HeapSort<T>::sorting_test(int iterations, int size) {
    char* time_file = generate_time_results_filename(size);
    ofstream plik(time_file);

    for (int i = 0; i< iterations; i++) {
        NumberGenerator<T> number_generator;
        Timer timer;
        Sort<T> sort;

        cout << "test nr " << i << endl;
        T* data = new T[size];
        for(int j = 0; j < size; j++) {
            data[j] = number_generator.generate();
        }
        timer.start();
        T* sorted_data = this->sort(data, size);
        timer.stop();
        bool is_sorted = sort.is_sorted(sorted_data, size);

        if (!is_sorted) {
            cout << "Sorting failed!" << endl;
        }
        else {
            FileHandler<T> file_handler;
            int time_result = timer.result();
            plik << time_result << endl;
            char* filename = generate_filename(size);
            file_handler.writeData(filename, size, sorted_data);
        }
        delete[] sorted_data;
    }
}
template<typename T>
void HeapSort<T>::sorting_file(char* filename) {
    FileHandler<T> file_handler;
    Timer timer;
    Sort<T> sort;

    int size = file_handler.numberOfValues(filename);
    T* data = file_handler.readData(filename);

    char* time_file = generate_time_results_filename(size);
    ofstream plik(time_file);

    timer.start();
    T* sorted_data = this->sort(data, size);
    timer.stop();
    bool is_sorted = sort.is_sorted(sorted_data, size);
    if (!is_sorted) {
        cout << "Sorting failed!" << endl;
    }
    else {
        cout << "Sorting successful!" << endl;
        int time_result = timer.result();
        plik << time_result << endl;
        char* filename_sorted = generate_filename(size);
        file_handler.writeData(filename_sorted, size, sorted_data);
    }
}



template<typename T>
void HeapSort<T>::heapify(T *data, int size, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // If the left child is larger than the root
    if (l < size && data[l] > data[largest])
        largest = l;

    // If the right child is larger
    if (r < size && data[r] > data[largest])
        largest = r;

    // If the root is not the largest
    if (largest != i) {
        swap(data[i], data[largest]);

        // Heapifying the sub-tree repeatedly
        heapify(data, size, largest);
    }
}


template <typename T>
char* HeapSort<T>::generate_time_results_filename(int size) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "Times-HeapSort-"
             << typeid(T).name() << "-"
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
template <typename T>
char* HeapSort<T>::generate_filename(int size) {
    const auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "HeapSort-"
             << typeid(T).name() << "-"
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

template class HeapSort<int>;
template class HeapSort<float>;
template class HeapSort<double>;

