#include "DrunkStudent.h"
#include "../utils/Timer.h"
#include "../utils/FileHandler.h"
#include "../utils/NumberGenerator.h"
#include "../sorting_algorithms/Sort.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;
using namespace chrono;

template<typename T>
DrunkStudent<T>::DrunkStudent(){};

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
        T* sorted_data = this->sort(data, 0, size - 1);
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

    sort.sort_array_for_test2(data, size ,distribution);

    timer.start();
    T* sorted_data = this->sort(data, 0, size - 1);
    timer.stop();
    bool is_sorted = sort.is_sorted(sorted_data, size);
    if (!is_sorted) {
        cout << "Sorting failed!" << endl;
    }
    else {
        cout << "Sorting successful!" << endl;
        int time_result = timer.result();
        plik << time_result << endl;

        char* filename_sorted = generate_filename(size, distribution);
        file_handler.writeData(filename_sorted, size, sorted_data);
        delete[] filename_sorted;
    }
    delete[] data;
    delete[] time_file;
}

template<typename T>
int DrunkStudent<T>::partition(T* data, int left, int right) {
    int pivotIndex = rand() % (right - left + 1) + left;
    T pivot = data[pivotIndex];
    std::swap(data[pivotIndex], data[right]);

    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (data[j] <= pivot) {
            i++;
            std::swap(data[i], data[j]);
        }
    }

    if (rand() % 3 == 0) {
        int randomIndex1 = rand() % (right - left + 1) + left;
        int randomIndex2 = rand() % (right - left + 1) + left;
        std::swap(data[randomIndex1], data[randomIndex2]);
    }

    swap(&data[i + 1], &data[right]);
    return i + 1;
}

template<typename T>
T* DrunkStudent<T>::sort(T* data, int left, int right) {
    if (left < right) {
        int p = partition(data, left, right);

        if (rand() % 2 == 0) {
            sort(data, left, p - 1);
            sort(data, p + 1, right);
        } else {
            sort(data, left, p - 1);
        }
    }
    return data;
}


template<typename T>
void DrunkStudent<T>::swap(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
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
    const auto now = system_clock::now();
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

template class DrunkStudent<int>;
template class DrunkStudent<float>;
template class DrunkStudent<double>;
