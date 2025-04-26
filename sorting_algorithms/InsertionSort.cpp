
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

//standard Insertion Sort algorithm
template<typename T>
T* InsertionSort<T>::sort(T *data, int size) {
    //temporary variable to hold the current value we're inserting
    T temp;

    //we start from the second element (index 1) because the first is already "sorted"
    for(int i = 1; i < size; i++) {
        temp = data[i]; //take the current value
        int j = i - 1;

        //shift elements that are greater than temp one position to the right
        while(j >= 0 && data[j] > temp) {
            data[j+1] = data[j];
            j--;
        }

        //place temp in its correct sorted position
        data[j+1] = temp;
    }

    return data;
}

//method for automated testing of the sorting algorithm with generated data
template<typename T>
void InsertionSort<T>::sortingTest(int iterations, int size, int distribution) {
    //generate a filename where we'll save time results
    char* timeFile = generateTimeResultsFilename(size, distribution);
    ofstream plik(timeFile);

    //perform the test 'iterations' number of times
    for (int i = 0; i < iterations; i++) {
        NumberGenerator<T> numberGenerator; //random data generator
        Timer timer;                         //measures execution time
        Sort<T> sort;                        //utility for additional sorting logic

        cout << "Test nr " << i + 1 << endl;

        //generate a fresh array of test data
        T* data = new T[size];
        for(int j = 0; j < size; j++) {
            data[j] = numberGenerator.generate();
        }

        //optionally pre-sort or scramble data based on distribution type
        sort.sortArrayForTest2(data, size, distribution);
        /*for (int i = 0 ;i<size; i++) {
            cout<<data[i]<< endl;
        }*/
        //time how long our sort takes
        timer.start();
        this->sort(data, size);
        timer.stop();

        //check if sorting was successful
        bool isSorted = sort.isSorted(data, size);
        if (!isSorted) {
            cout << "Sorting failed!" << endl;
        } else {
            cout << "Sorting successful!" << endl;
            FileHandler<T> fileHandler;

            //save the time result to a csv file
            int timeResult = timer.result();
            plik << timeResult << endl;

            //save the sorted array to a uniquely named file
            char* filename = generateFilename(size, distribution, i);
            fileHandler.writeData(filename, size, data);
            delete[] filename;
        }

        delete[] data;
    }

    delete[] timeFile;
}

//sort data from a file instead of generating it, useful for manual testing
template<typename T>
void InsertionSort<T>::sortingFile(char* filename, int distribution) {
    FileHandler<T> fileHandler;
    Timer timer;
    Sort<T> sort;

    //read the size and contents of the file
    int size = fileHandler.numberOfValues(filename);
    T* data = fileHandler.readData(filename);

    //generate output filename for timing results
    char* timeFile = generateTimeResultsFilename(size, distribution);
    ofstream plik(timeFile);

    //shuffle or presort the data based on distribution
    sort.sortArrayForTest2(data, size, distribution);


    //time the sorting process
    timer.start();
    this->sort(data, size);
    timer.stop();

    //validate correctness and save results
    bool isSorted = sort.isSorted(data, size);
    if (!isSorted) {
        cout << "Sorting failed!" << endl;
    } else {
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

//utility function to generate a filename for storing time results
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

    //convert the stringstream into a dynamically allocated C-string
    std::string s = filename.str();
    char* result = new char[s.length() + 1];
    strcpy(result, s.c_str());

    return result;
}

//utility function to generate a filename for storing sorted arrays
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

    //convert the stringstream into a dynamically allocated C-string
    std::string s = filename.str();
    char* result = new char[s.length() + 1];
    strcpy(result, s.c_str());

    return result;
}

//explicit template instantiations to support int, float, and double
template class InsertionSort<int>;
template class InsertionSort<float>;
template class InsertionSort<double>;
