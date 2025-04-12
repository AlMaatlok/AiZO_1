#include "ShellSort.h"

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

template<typename T>
ShellSort<T>::ShellSort() {}

template<typename T>
T* ShellSort<T>::sort(T* data, int size, gap givenGap) {
    if (givenGap == SHELL) {
        for (int gap = size / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < size; i++) {
                T temp = data[i];
                int j;
                for (j = i; j >= gap && data[j - gap] > temp; j -= gap)
                    data[j] = data[j - gap];
                data[j] = temp;
            }
        }
    } else if (givenGap == HIBBARD) {
        int x = 1;
        int gap = (1 << x) - 1;

        while (gap < size)
            gap = (1 << ++x) - 1;

        --x;

        while (x > 0) {
            gap = (1 << x) - 1;
            for (int i = gap; i < size; i++) {
                T temp = data[i];
                int j;
                for (j = i; j >= gap && data[j - gap] > temp; j -= gap)
                    data[j] = data[j - gap];
                data[j] = temp;
            }
            --x;
        }
    }

    return data;
}


template <typename T>
void ShellSort<T>::sorting_test(int iterations, int size, gap givenGap) {
    char* time_file = generate_time_results_filename(givenGap, size);
    std::ofstream plik(time_file);

    for (int i = 0; i < iterations; i++) {
        NumberGenerator<T> number_generator;
        Timer timer;
        Sort<T> sort;

        std::cout << "Test nr " << i + 1 << std::endl;
        T* data = new T[size]; // Dynamiczna alokacja tablicy
        for (int j = 0; j < size; j++) {
            data[j] = number_generator.generate(); // Generowanie danych
        }

        timer.start();
        T* sorted_data = this->sort(data, size, givenGap);
        timer.stop();

        bool is_sorted = sort.is_sorted(sorted_data, size);
        if (!is_sorted) {
            std::cout << "Sorting failed!" << std::endl;
        } else {
            FileHandler<T> file_handler;
            std::cout << "Sorting successful!" << std::endl;
            int time_result = timer.result();
            plik << time_result << std::endl;
            char* filename = generate_filename(givenGap, size);
            file_handler.writeData(filename, size, sorted_data);
        }

        delete[] data; // Zwolnienie pamięci po sortowaniu
    }

    delete[] time_file; // Zwolnienie pamięci po pliku
}

template <typename T>
void ShellSort<T>::sorting_file(char* filename, gap givenGap) {
    FileHandler<T> file_handler;
    Timer timer;
    Sort<T> sort;

    int size = file_handler.numberOfValues(filename);
    T* data = file_handler.readData(filename);

    char* time_file = generate_time_results_filename(givenGap, size);
    std::ofstream plik(time_file);

    timer.start();
    T* sorted_data = this->sort(data, size, givenGap);
    timer.stop();

    bool is_sorted = sort.is_sorted(sorted_data, size);
    if (!is_sorted) {
        cout << "Sorting failed!" << std::endl;
    } else {
        cout << "Sorting successful!" << std::endl;
        int time_result = timer.result();
        plik << time_result << std::endl;
        char* filename_sorted = generate_filename(givenGap, size);
        file_handler.writeData(filename_sorted, size, sorted_data);
    }

    delete[] data;
    delete[] time_file;
}

template <typename T>
char* ShellSort<T>::generate_filename(gap givenGap, int size) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    std::stringstream filename;
    filename << "ShellSort-";

    if (givenGap == SHELL)
        filename << "SHELL-";
    else if (givenGap == HIBBARD)
        filename << "HIBBARD-";
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
char* ShellSort<T>::generate_time_results_filename(gap givenGap, int size) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    std::stringstream filename;
    filename << "Times-ShellSort-";

    if (givenGap == SHELL)
        filename << "SHELL-";
    else if (givenGap == HIBBARD)
        filename << "HIBBARD-";
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

template class ShellSort<int>;
template class ShellSort<float>;
template class ShellSort<double>;
