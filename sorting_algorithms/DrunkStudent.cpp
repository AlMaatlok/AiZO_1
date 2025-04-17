#include "DrunkStudent.h"

#include <fstream>
#include <iostream>
#include <cstring>

#include "../utils/FileHandler.h"
#include "../utils/NumberGenerator.h"
#include "../utils/Timer.h"
#include "Sort.h"

template<typename T>
DrunkStudent<T>::DrunkStudent() {
}

template<typename T>
T* DrunkStudent<T>::sort(T* data, int size) {
    // build min-heap
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(data, size, i);

    // extracting element from the heap
    for (int i = size - 1; i >= 0; i--) {
        // moving the current root to the last element of the array.
        T temp = data[i];
        data[i] = data[0];
        data[0] = temp;

        // calling max heapify on the shrink heap
        heapify(data, i, 0);
    }

    Sort<T> sort;
    bool isSorted = sort.is_sorted(data, size);
    if (!isSorted) {
        reverseArray(data, size);
    }

    return data;
}

template<typename T>
void DrunkStudent<T>::sorting_test(int iterations, int size, int distribution) {
    char* time_file = generate_time_results_filename(size, distribution);
    ofstream plik(time_file);

    for (int i = 0; i< iterations; i++) {
        NumberGenerator<T> number_generator;
        Timer timer;
        Sort<T> sort;

        cout << "Test nr " << i << endl;
        T* data = new T[size];
        for(int j = 0; j < size; j++) {
            data[j] = number_generator.generate();
        }
        sort.sort_array_for_test2(data, size, distribution);

        timer.start();
        T* sorted_data = this->sort(data, size);
        timer.stop();
        bool is_sorted = sort.is_sorted(sorted_data, size);

        if (!is_sorted) {
            cout << "Sorting failed!" << endl;
        }
        else {
            cout << "Sorting successful!" << endl;
            FileHandler<T> file_handler;
            int time_result = timer.result();
            plik << time_result << endl;

            char* filename = generate_filename(size, distribution);
            file_handler.writeData(filename, size, sorted_data);
            delete[] filename;
        }
        delete[] data;
    }
    delete[] time_file;
}

template<typename T>
void DrunkStudent<T>::sorting_file(char* filename, int distribution) {
    FileHandler<T> file_handler;
    Timer timer;
    Sort<T> sort;

    int size = file_handler.numberOfValues(filename);
    T* data = file_handler.readData(filename);

    char* time_file = generate_time_results_filename(size, distribution);
    ofstream plik(time_file);

    sort.sort_array_for_test2(data, size, distribution);

    timer.start();
    T* sorted_data = this->sort(data, size);
    timer.stop();
    bool is_sorted = sort.is_sorted(sorted_data, size);
    if (!is_sorted) {
        cout << "Sorting failed!" << endl;
    }
    else {
        cout << "Sorting successful";
        int time_result = timer.result();
        plik << time_result << endl;
        char* filename_sorted = generate_filename(size, distribution);
        file_handler.writeData(filename_sorted, size, sorted_data);
        delete[] filename_sorted;
    }
    delete[] data;
    delete[] time_file;
}


template <typename T>
char* DrunkStudent<T>::generate_time_results_filename(int size, int distribution) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "Times-DrunkStudent-"
             << typeid(T).name() << "-"
             << size << "-"
             << distribution << "-"
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
char* DrunkStudent<T>::generate_filename(int size, int distribution) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "DrunkStudent-"
             << typeid(T).name() << "-"
             << size << "-"
             << distribution << "-"
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

template<typename T>
void DrunkStudent<T>::heapify(T *data, int size, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // If the left child is larger than the root
    if (l < size && data[l] < data[smallest])
        smallest = l;

    // If the right child is larger
    if (r < size && data[r] < data[smallest])
        smallest = r;

    // If the root is not the largest
    if (smallest != i) {
        swap(&data[i], &data[smallest]);

        // Heapifying the sub-tree repeatedly
        heapify(data, size, smallest);
    }
}

template<typename T>
void DrunkStudent<T>::swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template<typename T>
void DrunkStudent<T>::reverseArray(T* data, int size) {
    for (int i = 0; i < size / 2; i++) {
        T temp = data[i];
        data[i] = data[size - i - 1];
        data[size - i - 1] = temp;
    }
}

template class DrunkStudent<int>;
template class DrunkStudent<float>;
template class DrunkStudent<double>;