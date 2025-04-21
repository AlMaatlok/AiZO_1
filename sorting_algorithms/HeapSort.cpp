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

//sorting function using max-heap
template<typename T>
T* HeapSort<T>::sort(T *data, int size) {
    // build max-heap
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(data, size, i);

    // extracting element from the heap
    for (int i = size - 1; i >= 0; i--) {
        // moving the current root to the last element of the array.
        T temp = data[i];
        data[i] = data[0];
        data[0] = temp;

        // calling max heapify on the reduced heap
        heapify(data, i, 0);
    }
    return data;
}

// function to run sorting test multiple times and save results
template<typename T>
void HeapSort<T>::sortingTest(int iterations, int size, int distribution) {
    char* timeFile = generateTimeResultsFilename(size, distribution); // generate name for results file
    ofstream plik(timeFile); // open file for writing

    for (int i = 0; i < iterations; i++) {
        NumberGenerator<T> numberGenerator;
        Timer timer;
        Sort<T> sort;

        cout << "Test nr " << i + 1 << endl;

        T* data = new T[size]; // array for sorting

        // generate random numbers
        for (int j = 0; j < size; j++) {
            data[j] = numberGenerator.generate();
        }

        // apply chosen distribution to input array
        sort.sortArrayForTest2(data, size, distribution);

        // measure sorting time
        timer.start();
        this->sort(data, size);
        timer.stop();

        bool isSorted = sort.isSorted(data, size);

        if (!isSorted) {
            cout << "Sorting failed!" << endl;
        } else {
            cout << "Sorting successful!" << endl;

            FileHandler<T> fileHandler;
            int timeResult = timer.result();
            plik << timeResult << endl;

            // save sorted array to file
            char* filename = generateFilename(size, distribution, i);
            fileHandler.writeData(filename, size, data);
            delete[] filename;
        }
        delete[] data;
    }
    delete[] timeFile;
}

template<typename T>
void HeapSort<T>::sortingFile(char* filename, int distribution) {
    FileHandler<T> fileHandler;
    Timer timer;
    Sort<T> sort;

    int size = fileHandler.numberOfValues(filename);
    T* data = fileHandler.readData(filename);

    char* timeFile = generateTimeResultsFilename(size, distribution);
    ofstream plik(timeFile);

    sort.sortArrayForTest2(data, size ,distribution);

    timer.start();
    this->sort(data, size);
    timer.stop();
    bool isSorted = sort.isSorted(data, size);
    if (!isSorted) {
        cout << "Sorting failed!" << endl;
    }
    else {
        cout << "Sorting successful!" << endl;
        int timeResult = timer.result();
        plik << timeResult << endl;

        char* filenameSorted = generateFilename(size, distribution, 1);
        fileHandler.writeData(filenameSorted, size, data);
        delete[] filenameSorted;
    }
    delete[] data;
    delete[] timeFile;
}

template<typename T>
void HeapSort<T>::heapify(T *data, int size, int i) {
    int largest = i;         //initialize largest as root
    int l = 2 * i + 1;       //left child index
    int r = 2 * i + 2;       //right child index

    //if the left child is larger than the root
    if (l < size && data[l] > data[largest])
        largest = l;

    //if the right child is larger
    if (r < size && data[r] > data[largest])
        largest = r;

    //if the root is not the largest
    if (largest != i) {
        swap(data[i], data[largest]);

        //heapifying the sub-tree repeatedly
        heapify(data, size, largest);
    }
}


template <typename T>
char* HeapSort<T>::generateTimeResultsFilename(int size, int distribution) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "Times-HeapSort-"
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
char* HeapSort<T>::generateFilename(int size, int distribution, int nr) {
    const auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << "HeapSort-"
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

template class HeapSort<int>;
template class HeapSort<float>;
template class HeapSort<double>;

