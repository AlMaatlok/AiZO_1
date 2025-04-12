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
    int* gaps;
    int gapCount = 0;

    // Wybór odpowiedniego gapu
    if (givenGap == SHELL) {
        gaps = new int[size]; // maksymalnie size/2, więc tyle wystarczy
        gapCount = 0;
        int gapValue = size / 2;
        while (gapValue > 0) {
            gaps[gapCount++] = gapValue;
            gapValue /= 2;
        }
    } else if (givenGap == HIBBARD) {
        gaps = new int[size]; // bezpieczny zapas
        gapCount = 0;
        int k = 1;
        int gapValue;
        while ((gapValue = (1 << k) - 1) < size) { // użycie bitowego przesunięcia zamiast pow()
            gaps[gapCount++] = gapValue;
            k++;
        }
    } else {
        cout << "Unsupported gap sequence!" << std::endl;
        return nullptr; // Zwróć null jeśli nie obsługiwany gap
    }

    // Algorytm sortowania Shella
    for (int i = 0; i < gapCount; ++i) {
        int gap = gaps[i];
        for (int j = gap; j < size; ++j) {
            T temp = data[j];
            int k = j;
            while (k >= gap && data[k - gap] > temp) {
                data[k] = data[k - gap];
                k -= gap;
            }
            data[k] = temp;
        }
    }

    delete[] gaps; // Zwolnienie dynamicznej pamięci
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
