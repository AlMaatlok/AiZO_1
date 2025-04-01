#include "FileHandler.h"

#include <fstream>
#include <iostream>
#include <ostream>

using namespace std;

template <typename T>       //function to read first line, how many values is in the file
int FileHandler<T>::numberOfValues(const string& fileName) {
    if (ifstream file(fileName); !file.is_open()) {
        cerr << "File " << fileName << " could not be opened" << endl;
        return -1;
    }
    else {
        int count = 0;
        file >> count;
        return count;
    }
}

template <typename T>         //function to read data from a file
T* FileHandler<T>::readData(const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error opening file " << fileName << endl;
        return nullptr;
    }
    int count = 0;
    file >> count;

    if (count < 1) {
        cerr << "Error reading file " << fileName << endl;
        return nullptr;
    }
    T* data = static_cast<T*>(malloc(sizeof(T) * count));

    if (!data) {
        cerr << "Error allocating memory for data" << endl;
    }
    else {
        for (int i = 0; i < count; i++) {
            file >> data[i];
        }
    }
    file.close();
    return data;
}
template<typename T>         //function to write generated data to a file
void FileHandler<T>::writeData(const string &fileName, int count, const T *data) {
    ofstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error opening file " << fileName << endl;
    }
    else {
        file << count << endl;

        for (int i = 0; i < count; i++) {
            file << data[i] << endl;
        }
        file.close();
    }
}

template class FileHandler<int>;
template class FileHandler<float>;
template class FileHandler<double>;