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

//constructor - seed the random number generator
template<typename T>
QuickSort<T>::QuickSort() {
    srand(time(nullptr));
}

//recursive QuickSort function
template <typename T>
T* QuickSort<T>::sort(T* data, int left, int right, pivotIndex pivotInd) {
    if (left < right) {
        int pivot = partition(data, left, right, pivotInd); //partition the array
        sort(data, left, pivot - 1, pivotInd); //sort left partition
        sort(data, pivot + 1, right, pivotInd); //sort right partition
    }
    return data;
}

//run sorting performance test with generated data
template <typename T>
void QuickSort<T>::sortingTest(int iterations, int size, pivotIndex pivot, int distribution) {
    char* timeFile = generateTimeResultsFilename(pivot, size, distribution);
    ofstream plik(timeFile);
    delete[] timeFile;

    for (int i = 0; i < iterations; i++) {
        NumberGenerator<T> numberGenerator;
        Timer timer;
        Sort<T> sort;

        cout << "Test nr " << i + 1 << endl;

        //generate array of random values
        T* data = new T[size];
        for (int j = 0; j < size; j++) {
            data[j] = numberGenerator.generate();
        }

        //modify data according to selected distribution type
        sort.sortArrayForTest2(data, size, distribution);

        //start timer and perform sort
        timer.start();
        this->sort(data, 0, size - 1, pivot);
        timer.stop();

        //verify sorting correctness and write results
        bool isSorted = sort.isSorted(data, size);
        if (!isSorted) {
            cout << "Sorting failed!" << endl;
        } else {
            cout << "Sorting successful!" << endl;
            FileHandler<T> fileHandler;
            int timeResult = timer.result();
            plik << timeResult << endl;

            char* filename = generateFilename(pivot, size, distribution, i);
            fileHandler.writeData(filename, size, data);
            delete[] filename;
        }

        delete[] data;
    }
}

//perform sorting on data loaded from a file
template <typename T>
void QuickSort<T>::sortingFile(char* filename, pivotIndex pivot, int distribution) {
    FileHandler<T> fileHandler;
    Timer timer;
    Sort<T> sort;

    //read data from the input file
    int size = fileHandler.numberOfValues(filename);
    T* data = fileHandler.readData(filename);

    //generate output file for timing results
    char* timeFile = generateTimeResultsFilename(pivot, size, distribution);
    ofstream plik(timeFile);
    delete[] timeFile;

    //apply test distribution
    sort.sortArrayForTest2(data, size, distribution);

    //sort and time it
    timer.start();
    this->sort(data, 0, size - 1, pivot);
    timer.stop();

    //verify sort and write results
    bool isSorted = sort.isSorted(data, size);
    if (!isSorted) {
        cout << "Sorting failed!" << endl;
    }
    else {
        cout << "Sorting";
        int timeResult = timer.result();
        plik << timeResult << endl;

        char* filenameSorted = generateFilename(pivot, size, distribution, 1);
        fileHandler.writeData(filenameSorted, size, data);
        delete[] filenameSorted;
    }
    delete[] data;
}

//partition method using selected pivot strategy
template<typename T>
int QuickSort<T>::partition(T *data, int left, int right, pivotIndex pivot) {
    int pivotIndex;

    //determine pivot position
    if (pivot == FIRST) {
        pivotIndex = left;
    } else if (pivot == LAST) {
        pivotIndex = right;
    } else if (pivot == MIDDLE) {
        pivotIndex = left + (right - left) / 2;
    } else if (pivot == RANDOM) {
        pivotIndex = left + (rand() % (right - left + 1));
    } else {
        pivotIndex = left + (right - left) / 2;
    }

    //move pivot to end for partitioning
    swap(&data[pivotIndex], &data[right]);
    T pivotValue = data[right];

    //rearrange elements around pivot
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (data[j] <= pivotValue) {
            i++;
            swap(&data[i], &data[j]);
        }
    }
    swap(&data[i + 1], &data[right]);
    return i + 1; //return pivot's final position
}

//utility swap function
template<typename T>
void QuickSort<T>::swap(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

//generate unique filename for sorted data
template <typename T>
char* QuickSort<T>::generateFilename(pivotIndex pivot, int size, int distribution, int nr) {
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

//generate unique filename for timing results
template <typename T>
char* QuickSort<T>::generateTimeResultsFilename(pivotIndex pivot, int size, int distribution) {
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

//explicit template instantiations for supported types
template class QuickSort<int>;
template class QuickSort<float>;
template class QuickSort<double>;
