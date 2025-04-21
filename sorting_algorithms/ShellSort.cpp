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
T* ShellSort<T>::sort(T* data, int size, int* gaps, int gapCount) {
    for (int g = 0; g < gapCount; g++) {
        int currentGap = gaps[g];
        for (int i = currentGap; i < size; i++) {
            T temp = data[i];
            int j;
            for (j = i; j >= currentGap && data[j - currentGap] > temp; j -= currentGap) {
                data[j] = data[j - currentGap];
            }
            data[j] = temp;
        }
    }
    return data;
}


template <typename T>
void ShellSort<T>::sortingTest(int iterations, int size, gap givenGap, int distribution) {
    char* timeFile = generateTimeResultsFilename(givenGap, size, distribution);    //file to store time results
    ofstream plik(timeFile);

    int gapCount = 0;       //number of gaps
    int* gaps = generateGaps(size, givenGap, &gapCount);   //generating gaps

    for (int i = 0; i < iterations; i++) {
        NumberGenerator<T> numberGenerator;
        Timer timer;
        Sort<T> sort;

        std::cout << "Test nr " << i + 1 << std::endl;
        T* data = new T[size]; // dynimac allocation
        for (int j = 0; j < size; j++) {
            data[j] = numberGenerator.generate(); // generating random data
        }

        sort.sortArrayForTest2(data, size, distribution);

        timer.start();
        this->sort(data, size, gaps, gapCount);   //sorting with Shell Sort
        timer.stop();

        bool isSorted = sort.isSorted(data, size);    //checking if sorting was successful
        if (!isSorted) {
            std::cout << "Sorting failed!" << std::endl;
        } else {
            FileHandler<T> fileHandler;
            std::cout << "Sorting successful!" << std::endl;
            int time_result = timer.result();
            plik << time_result << std::endl;     //writing time result into a file  .csv

            char* filename = generateFilename(givenGap, size, distribution, i);    //file for sorted values
            fileHandler.writeData(filename, size, data);   //writing sorted data into a file .txt
            delete[] filename;
        }

        delete[] data; //freeing memory
    }

    delete[] timeFile; //freeing memory
}

template <typename T>
void ShellSort<T>::sortingFile(char* filename, gap givenGap, int distribution) {
    FileHandler<T> fileHandler;
    Timer timer;
    Sort<T> sort;

    int size = fileHandler.numberOfValues(filename);
    T* data = fileHandler.readData(filename);

    char* timeFile = generateTimeResultsFilename(givenGap, size, distribution);
    ofstream plik(timeFile);

    int gapCount = 0;
    int* gaps = generateGaps(size, givenGap, &gapCount);

    sort.sortArrayForTest2(data, size, distribution);

    timer.start();
    this->sort(data, size, gaps, gapCount);
    timer.stop();

    bool isSorted = sort.isSorted(data, size);
    if (!isSorted) {
        cout << "Sorting failed!" << std::endl;
    } else {
        cout << "Sorting successful!" << std::endl;
        int timeResult = timer.result();
        plik << timeResult << std::endl;
        char* filenameSorted = generateFilename(givenGap, size, distribution, 1);
        fileHandler.writeData(filenameSorted, size, data);
    }

    delete[] data;
    delete[] timeFile;
    delete[] gaps;
}

template <typename T>
char* ShellSort<T>::generateFilename(gap givenGap, int size, int distribution, int nr) {
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
             << distribution << "-"
             << (timeInfo->tm_year + 1900) << "-"
             << (timeInfo->tm_mon + 1) << "-"
             << (timeInfo->tm_mday) << "-"
             << (timeInfo->tm_hour) << "."
             << (timeInfo->tm_min) << "."
             << (timeInfo->tm_sec) << "-"
             << "test-" << nr << ".txt";

    std::string s = filename.str();
    char* result = new char[s.length() + 1];
    strcpy(result, s.c_str());

    return result;
}

template <typename T>
char* ShellSort<T>::generateTimeResultsFilename(gap givenGap, int size, int distribution) {
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
int* ShellSort<T>::generateGaps(int size, gap givenGap, int* count) {
    int *gaps = nullptr;
    *count = 0;

    if (givenGap == SHELL) {
        for (int gap = size / 2; gap > 0; gap /= 2) {
            int *temp = static_cast<int *>(realloc(gaps, (*count + 1) * sizeof(int)));
            if (!temp) {
                free(gaps);
                cout << "Memory allocation failed!" << endl;
            }
            gaps = temp;
            gaps[(*count)++] = gap;
        }
    } else if (givenGap == HIBBARD) {
        int k = 1, gap = 1;
        while (gap < size) {
            int *temp = static_cast<int *>(realloc(gaps, (*count + 1) * sizeof(int)));
            if (!temp) {
                free(gaps);
                cout << "Memory allocation failed!" << endl;
            }
            gaps = temp;
            gaps[(*count)++] = gap;

            k++;
            gap = (1 << k) - 1; // 2^k - 1
        }
        for (int i = 0; i < *count / 2; i++) {
            int tmp = gaps[i];
            gaps[i] = gaps[*count - 1 - i];
            gaps[*count - 1 - i] = tmp;
        }
    }

    return gaps;
}

template class ShellSort<int>;
template class ShellSort<float>;
template class ShellSort<double>;
