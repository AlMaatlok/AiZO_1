#include <chrono>
#include <iostream>
#include <fstream>

#include "utils/FileHandler.h"
#include "utils/NumberGenerator.h"
#include "utils/Timer.h"

using namespace std;
using namespace chrono;

template <typename T>
string generateFilename();
void helpMode();

int main(int cntArguments, char** args) {

    if (cntArguments < 6) {
        helpMode();
        return -1;
    }

    string mode = args[1];
    if (mode == "--file") {
        cout << "file";

        int sortingType = atoi(args[2]);
        int dataType = atoi(args[3]);
        string filename = args[4];
        string output = args[5];

        //Shell Sort
        if (sortingType == 0) {}

        //Heap Sort
        else if (sortingType == 1) {}

        //Insrtion Sort
        else if (sortingType == 2) {}

        //Quick Sort
        else if (sortingType == 3) {}
        else {
            cout << "Error!" << endl <<
                    "Argument for type of sorting must be from 0 to 3" << endl;
            helpMode();

            return -2;
        }
    }
    else if (mode == "--test") {
        cout << "test";
    }
    else {
        cout << "Specify mode you would like to enter (file/test)" << endl;
        helpMode();
    }
    /*Timer time;
    constexpr int count2 = 12;
    double* data = nullptr;

    ofstream plik("wyniki.csv");
    plik << "time\n";

    NumberGenerator<double> number_generator;

    //timer.start();
    for (int i = 0; i < 12; i++) {
        timer.start();
        // memory alocation for each value
        double* current_data = new double;
        *current_data = number_generator.generate();
        std::cout << *current_data << std::endl;


        for (int j = 0; j < 1000; j++) {
            *current_data = *current_data / count2;
            *current_data *= 4;
            cout << *current_data << endl;
        }


        if (data == nullptr) {
            data = current_data;
        }

        delete current_data;
        timer.stop();
        int result = timer.result();
        plik << result << "\n";
    }*/
    /*timer.stop();
    int time = timer.result();
    std::cout << time << std::endl;

    plik << time << "\n";#1#
    string filename = generateFilename<double>();
    FileHandler<double>::writeData(filename, count2, data);

    delete[] data; */


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


    //FileHandler<int>::freeMemory(intData);

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

void helpMode() {
    cout <<     "FILE TEST MODE:" << endl <<
                "   Usage:" << endl <<
                "    ./YourProject --file <algorithm> <type> <inputFile> [outputFile]" << endl <<
                "   <algorithm> Sorting algorithm to use (e.g., 0 - Shell, 1 - Heap, 2 - Insertion, 3 - Quick)." << endl <<
                "   <type> Data type to load (0 - int, 1 - float, 2 - double)." << endl <<
                "   <inputFile> Input file containing the data to be sorted." << endl <<
                "   [outputFile] If provided, the sorted values will be saved to this file" << endl <<
                endl <<
                "BENCHMARK MODE:" << endl <<
                "   Usage:" << endl <<
                "    ./YourProject --test <algorithm> <type> <size> <outputFile>" << endl <<
                "   <algorithm> Sorting algorithm to use (0 - Shell, 1 - Heap, 2 - Insertion, 3 - Quick)." << endl <<
                "   <type> Data type to generate (0 - int, 1 - float, 2 - double)." << endl <<
                "   <size> Number of elements to generate (instance size)." << endl <<
                "   <outputFile> File where the benchmark results should be saved." << endl <<
                endl <<
                "HELP MODE:" << endl <<
                "   Usage:" << endl <<
                "    ./YourProject --help" << endl <<
                "   Displays this help message." << endl <<
                "   Notes:" << endl <<
                "   - The help message will also appear if no argumnets are provides." << endl <<
                "   - Ensure that either --file or --test mode id specified;" << endl <<
                "     they are mutually exclusive." << endl <<
                "EXAMPLE CALLS:" << endl <<
                "    Sorting integers using Heap Sort from file and saving results:" << endl <<
                "      ./YourProject --file 1 0 input.txt sorted_output.txt" << endl <<
                endl <<
                "    Running a benchmark with 1000 randomly generated floats using Shell Sort:" << endl <<
                "      ./YourProject --test 0 1 1000 results.txt";
}