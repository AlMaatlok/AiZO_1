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
void InsertionSort<T>::sortingTest(int iterations, int size, int distribution) {
    char* timeFile = generateTimeResultsFilename(size, distribution);
    ofstream plik(timeFile);

    for (int i = 0; i< iterations; i++) {
        NumberGenerator<T> numberGenerator;
        Timer timer;
        Sort<T> sort;

        cout << "Test nr " << i + 1 << endl;
        T* data = new T[size];
        for(int j = 0; j < size; j++) {
            data[j] = numberGenerator.generate();
        }
        sort.sortArrayForTest2(data, size, distribution);

        timer.start();
        this->sort(data, size);
        timer.stop();
        bool isSorted = sort.isSorted(data, size);

        if (!isSorted) {
            cout << "Sorting failed!" << endl;
        }
        else {
            cout << "Sorting successful!" << endl;
            FileHandler<T> fileHandler;
            int timeResult = timer.result();
            plik << timeResult << endl;

            char* filename = generateFilename(size, distribution, i);
            fileHandler.writeData(filename, size, data);
            delete[] filename;
        }
        delete[] data;
    }
    delete[] timeFile;
}

template<typename T>
void InsertionSort<T>::sortingFile(char* filename, int distribution) {
    FileHandler<T> fileHandler;
    Timer timer;
    Sort<T> sort;

    int size = fileHandler.numberOfValues(filename);
    T* data = fileHandler.readData(filename);

    char* timeFile = generateTimeResultsFilename(size, distribution);
    ofstream plik(timeFile);

    sort.sortArrayForTest2(data, size, distribution);

    timer.start();
    this->sort(data, size);
    timer.stop();
    bool isSorted = sort.isSorted(data, size);
    if (!isSorted) {
        cout << "Sorting failed!" << endl;
    }
    else {
        cout << "Sorting successful";
        int timeResult = timer.result();
        plik << timeResult << endl;
        char* filenameSorted = generateFilename(size, distribution, 1);
        fileHandler.writeData(filenameSorted, size, data);
        delete[] filenameSorted;
    }
    delete[] data;
    delete[] timeFile;
}


template <typename T>
char* InsertionSort<T>::generateTimeResultsFilename(int size, int distribution) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "Times-InsertSort-"
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
char* InsertionSort<T>::generateFilename(int size, int distribution, int nr) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "InsertSort-"
             << typeid(T).name() << "-"
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

template class InsertionSort<int>;
template class InsertionSort<float>;
template class InsertionSort<double>;