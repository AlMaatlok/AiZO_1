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

//sorting method using ShellSort algorithm
template<typename T>
T* ShellSort<T>::sort(T* data, int size, int* gaps, int gapCount) {
    //iterate over all gaps
    for (int g = 0; g < gapCount; g++) {
        int currentGap = gaps[g];
        //perform insertion sort for each gap
        for (int i = currentGap; i < size; i++) {
            T temp = data[i];
            int j;
            //compare elements at the given gap
            for (j = i; j >= currentGap && data[j - currentGap] > temp; j -= currentGap) {
                data[j] = data[j - currentGap];
            }
            data[j] = temp;  //place the element in the correct position
        }
    }
    return data;
}

//method to perform sorting tests multiple times, with timing results stored in a file
template <typename T>
void ShellSort<T>::sortingTest(int iterations, int size, gap givenGap, int distribution) {
    //generate filename for storing time results
    char* timeFile = generateTimeResultsFilename(givenGap, size, distribution);
    ofstream plik(timeFile);

    int gapCount = 0;
    //generate gaps for ShellSort based on the given gap type
    int* gaps = generateGaps(size, givenGap, &gapCount);

    //perform tests for the specified number of iterations
    for (int i = 0; i < iterations; i++) {
        NumberGenerator<T> numberGenerator;
        Timer timer;
        Sort<T> sort;

        std::cout << "Test number " << i + 1 << std::endl;
        T* data = new T[size];  //dynamically allocate memory for the array
        for (int j = 0; j < size; j++) {
            data[j] = numberGenerator.generate();  //generate random numbers
        }

        //apply distribution to the data
        sort.sortArrayForTest2(data, size, distribution);

        //start the timer and perform the sorting
        timer.start();
        this->sort(data, size, gaps, gapCount);
        timer.stop();

        //check if sorting was successful
        bool isSorted = sort.isSorted(data, size);
        if (!isSorted) {
            std::cout << "Sorting failed!" << std::endl;
        } else {
            FileHandler<T> fileHandler;
            std::cout << "Sorting successful!" << std::endl;
            int time_result = timer.result();
            plik << time_result << std::endl;  //write timing result to a file

            //generate filename for the sorted data and write the sorted array
            char* filename = generateFilename(givenGap, size, distribution, i);
            fileHandler.writeData(filename, size, data);
            delete[] filename;  //clean up memory for the filename
        }

        delete[] data;  //free dynamically allocated memory
    }

    delete[] timeFile;  //free dynamically allocated memory for the time file
}

//method to perform sorting on data from a file
template <typename T>
void ShellSort<T>::sortingFile(char* filename, gap givenGap, int distribution) {
    FileHandler<T> fileHandler;
    Timer timer;
    Sort<T> sort;

    //read the data from the file
    int size = fileHandler.numberOfValues(filename);
    T* data = fileHandler.readData(filename);

    //generate filename for storing time results
    char* timeFile = generateTimeResultsFilename(givenGap, size, distribution);
    ofstream plik(timeFile);

    int gapCount = 0;
    //generate gaps based on the given gap type
    int* gaps = generateGaps(size, givenGap, &gapCount);

    //apply distribution to the data
    sort.sortArrayForTest2(data, size, distribution);

    //start the timer and perform the sorting
    timer.start();
    this->sort(data, size, gaps, gapCount);
    timer.stop();

    //check if sorting was successful
    bool isSorted = sort.isSorted(data, size);
    if (!isSorted) {
        std::cout << "Sorting failed!" << std::endl;
    } else {
        std::cout << "Sorting successful!" << std::endl;
        int timeResult = timer.result();
        plik << timeResult << std::endl;  //write timing result to a file

        //generate filename for the sorted data and write the sorted array
        char* filenameSorted = generateFilename(givenGap, size, distribution, 1);
        fileHandler.writeData(filenameSorted, size, data);
    }

    delete[] data;  //free dynamically allocated memory
    delete[] timeFile;  //free dynamically allocated memory
    delete[] gaps;  //free dynamically allocated memory for gaps
}

//method to generate a filename based on the current date, gap type, and other parameters
template <typename T>
char* ShellSort<T>::generateFilename(gap givenGap, int size, int distribution, int nr) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    std::stringstream filename;
    filename << "ShellSort-";

    //add the gap type to the filename
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

//method to generate a filename for storing timing results, similar to generateFilename
template <typename T>
char* ShellSort<T>::generateTimeResultsFilename(gap givenGap, int size, int distribution) {
    auto now = system_clock::now();
    time_t timeNow = system_clock::to_time_t(now);

    tm* timeInfo = localtime(&timeNow);

    std::stringstream filename;
    filename << "Times-ShellSort-";

    // Add the gap type to the filename
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

//method to generate gaps based on the given gap type (SHELL or HIBBARD)
template <typename T>
int* ShellSort<T>::generateGaps(int size, gap givenGap, int* count) {
    int *gaps = nullptr;
    *count = 0;

    //generate gaps for SHELL type (halving the gap size)
    if (givenGap == SHELL) {
        for (int gap = size / 2; gap > 0; gap /= 2) {
            int *temp = static_cast<int *>(realloc(gaps, (*count + 1) * sizeof(int)));
            if (!temp) {
                free(gaps);
                std::cout << "Memory allocation failed!" << std::endl;
            }
            gaps = temp;
            gaps[(*count)++] = gap;
        }
    }
    //generate gaps for HIBBARD type (2^k - 1)
    else if (givenGap == HIBBARD) {
        int k = 1, gap = 1;
        while (gap < size) {
            int *temp = static_cast<int *>(realloc(gaps, (*count + 1) * sizeof(int)));
            if (!temp) {
                free(gaps);
                std::cout << "Memory allocation failed!" << std::endl;
            }
            gaps = temp;
            gaps[(*count)++] = gap;

            k++;
            gap = (1 << k) - 1; // 2^k - 1
        }
        //reverse the gap sequence
        for (int i = 0; i < *count / 2; i++) {
            int tmp = gaps[i];
            gaps[i] = gaps[*count - i - 1];
            gaps[*count - i - 1] = tmp;
        }
    }

    return gaps;
}


//explicit template instantiations for int, float, and double
template class ShellSort<int>;
template class ShellSort<float>;
template class ShellSort<double>;
