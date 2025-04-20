#include "DrunkStudent.h"

#include <fstream>
#include <iostream>
#include <cstring>

#include "../utils/FileHandler.h"
#include "../utils/NumberGenerator.h"
#include "../utils/Timer.h"
#include "Sort.h"

//constructor of DrunkStudent class
template<typename T>
DrunkStudent<T>::DrunkStudent() {
}

//sorting function using min-heap
template<typename T>
T* DrunkStudent<T>::sort(T* data, int size) {
    // build min-heap
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(data, size, i);

    // extracting elements from the heap
    for (int i = size - 1; i >= 0; i--) {
        // moving the current root to the last element of the array.
        T temp = data[i];
        data[i] = data[0];
        data[0] = temp;

        // calling max heapify on the reduced heap
        heapify(data, i, 0);
    }

    Sort<T> sort;
    bool isSorted = sort.isSorted(data, size);

    //reverse array if sorting failed
    if (!isSorted) {
        reverseArray(data, size);
    }

    return data;
}

//function to run sorting test multiple times
template<typename T>
void DrunkStudent<T>::sortingTest(int iterations, int size, int distribution) {
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
        sort.sortArrayForTst2(data, size, distribution);

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
void DrunkStudent<T>::sortingFile(char* filename, int distribution) {
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
char* DrunkStudent<T>::generateTimeResultsFilename(int size, int distribution) {
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
char* DrunkStudent<T>::generateFilename(int size, int distribution, int nr) {
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
             << (timeInfo->tm_sec) << "-"
             << "test-" << nr << ".txt";

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