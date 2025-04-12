#include "InsertionSort.h"

#include <fstream>
#include <iostream>
#include <cstring>

#include "../utils/FileHandler.h"
#include "../utils/NumberGenerator.h"
#include "../utils/Timer.h"
#include "Sort.h"

template<typename T>
InsertionSort<T>::InsertionSort() {
}

template<typename T>
T* InsertionSort<T>::sort(T *data, int size) {

    T temp;
    for(int i = 1; i < size; i++)
    {
        temp = data[i];
        int j = i - 1;

        while(j >= 0 && data[j] > temp)
        {
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = temp;
    }
    return data;
}

template<typename T>
void InsertionSort<T>::sorting_test(int iterations, int size) {
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
            cout << "Sorting successful!" << endl;
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
void InsertionSort<T>::sorting_file(char* filename) {
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
        cout << "Sorting succesful";
        int time_result = timer.result();
        plik << time_result << endl;
        char* filename_sorted = generate_filename(size);
        file_handler.writeData(filename_sorted, size, sorted_data);
    }
}


template <typename T>
char* InsertionSort<T>::generate_time_results_filename(int size) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "Times-InsertSort-"
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
char* InsertionSort<T>::generate_filename(int size) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "InsertSort-"
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

template class InsertionSort<int>;
template class InsertionSort<float>;
template class InsertionSort<double>;