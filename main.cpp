#include <chrono>
#include <iostream>

#include "utils/FileHandler.h"
#include "utils/NumberGenerator.h"

using namespace std;
using namespace chrono;

template <typename T>
string generateFilename();

int main(int cntArguments, char** args) {
    printf("aaa");
    cout << "hello";

    cout <<"world";
    int cokolwerer;
    scanf("%d", &cokolwerer);


    /*const string fileName = R"(C:\Users\HP\CLionProjects\proba\test.txt)";

    const int count = FileHandler<int>::numberOfValues(fileName);
    const int* intData = FileHandler<int>::readData(fileName);

    if (intData == nullptr) {
        cout << "File is empty" << endl;
        return 1;
    }
    cout << "File contains " << count << " values: " << endl;
    for (int i = 0; i < count; i++) {
        cout << intData[i] << endl;
    }*/

    NumberGenerator<double> number_generator;
    constexpr int count2 = 12;
    cout << count2 << endl;
    const auto data = static_cast<double*>(malloc(sizeof(double) * count2));
    for (int i = 0; i < count2; i++) {
        data[i]=number_generator.generate();
        cout << data[i] << endl;
    }
    const string filename = generateFilename<double>();
    FileHandler<double>::writeData(filename, count2, data);

    //FileHandler<int>::freeMemory(intData);
    /*if (argc < 5) {
        cout << "FILE TEST MODE: << endl << "
                "Usage:" << endl <<
                "./YourProject --file <algorithm> <type> <inputFile> [outputFile]" << endl <<
                "<algorithm> Sorting algorithm to use (e.g., 0 - Bubble, 1 - Merge, ...)." << endl <<
                "<type> Data type to load (e.g., 0 - int, 1 - float)." << endl <<
                "<inputFile> Input file containing the data to be sorted." << endl <<
                "[outputFile] If provided, the sorted values will be saved to this file" << endl <<
                "BENCHMARK MODE:" << endl <<
                "Usage:" << endl <<
                "./YourProject --test <algorithm> <type> <size> <outputFile>" << endl <<
                "<algorithm> Sorting algorithm to use (e.g., 0 - Bubble, 1 - Merge, ...)." << endl <<
                "<type> Data type to generate (e.g., 0 - int, 1 - float)." << endl <<
                "<size> Number of elements to generate (instance size)." << endl <<
                "<outputFile> File where the benchmark results should be saved.";

    }*/
    free(data);
    return 0;
}
template<typename T>         //function to generate name of a file based on the current date
string generateFilename() {
    const auto now = system_clock::now();
    const time_t nowTime = system_clock::to_time_t(now);

    const tm* timeInfo = localtime(&nowTime);
    stringstream filename;
    filename << typeid(T).name() << "-"
                << (timeInfo->tm_year + 1900) << "-"
                    << (timeInfo->tm_mon + 1) << "-"
                        << (timeInfo->tm_mday) << "-"
                            << (timeInfo->tm_hour) << "."
                                << (timeInfo->tm_min) << ".txt";

    return filename.str();
}