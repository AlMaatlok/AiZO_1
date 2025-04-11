#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include "sorting_algorithms/InsertionSort.h"
#include "utils/FileHandler.h"
#include "utils/NumberGenerator.h"
#include "utils/Timer.h"

using namespace std;
using namespace chrono;

template <typename T>
std::string generateFilename();
void helpMode();

int main(int cntArguments, char** args) {

    if (cntArguments < 5) {
        helpMode();
        return -1;
    }

    std::string mode = args[1];
    int sortingType = atoi(args[2]);
    int dataType = atoi(args[3]);

    if (mode == "--file") {
        cout << "file";
        char* filename = args[4];


        //Shell Sort
        if (sortingType == 0) {}

        //Heap Sort
        else if (sortingType == 1) {}

        //Insrtion Sort
        else if (sortingType == 2) {
            if (dataType == 0) {
                InsertionSort<int> insertion_sort;
                insertion_sort.sorting_file(filename);
            }
            else if (dataType == 1) {
                InsertionSort<float> insertion_sort;
                insertion_sort.sorting_file(filename);
            }
            else if (dataType == 2) {
                InsertionSort<double> insertion_sort;
                insertion_sort.sorting_file(filename);
            }
            else {
                cout << "Invalid argument for   data type" << endl;
            }
        }

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
        int number_of_tests = 10;
        int number_of_data = atoi(args[4]);
        //Shell Sort
        if (sortingType == 0) {}

        //Heap Sort
        else if (sortingType == 1) {}

        //Insrtion Sort
        else if (sortingType == 2) {
            if (dataType == 0) {
                InsertionSort<int> insertion_sort;
                insertion_sort.sorting_test(number_of_tests, number_of_data);
            }
            else if (dataType == 1) {
                InsertionSort<float> insertion_sort;
                insertion_sort.sorting_test(number_of_tests, number_of_data);
            }
            else if (dataType == 2) {
                InsertionSort<double> insertion_sort;
                insertion_sort.sorting_test(number_of_tests, number_of_data);
            }
            else {
                cout << "Wrong argument for data type!" << endl;
            }
        }

        //Quick Sort
        else if (sortingType == 3) {}
        else {
            cout << "Error!" << endl <<
                    "Argument for type of sorting must be from 0 to 3" << endl;
            helpMode();

            return -2;
        }

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
std::string generateFilename() {
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
                "    ./YourProject --file <algorithm> <type> <inputFile> [pivot/gap]" << endl <<
                "   <algorithm> Sorting algorithm to use (0 - Shell, 1 - Heap, 2 - Insertion, 3 - Quick)." << endl <<
                "   <type> Data type to load (0 - int, 1 - float, 2 - double)." << endl <<
                "   <inputFile> Input file containing the data to be sorted." << endl <<
                "   [pivot/gap] If provided, argument for pivot for Quick Sort (0 - first, 1 - last, 2 - middle, 3 - random)" << endl <<
                "               or for Shell Sort argument for gap (0 - Shell, 1 - Hibbard)" << endl <<
                endl <<
                "BENCHMARK MODE:" << endl <<
                "   Usage:" << endl <<
                "    ./YourProject --test <algorithm> <type> <size> [pivot/gap]" << endl <<
                "   <algorithm> Sorting algorithm to use (0 - Shell, 1 - Heap, 2 - Insertion, 3 - Quick)." << endl <<
                "   <type> Data type to generate (0 - int, 1 - float, 2 - double)." << endl <<
                "   <size> Number of elements to generate (instance size)." << endl <<
                "   [pivot/gap] If provided, argument for pivot for Quick Sort (0 - first, 1 - last, 2 - middle, 3 - random)" << endl <<
                "               or for Shell Sort argument for gap (0 - Shell, 1 - Hibbard)" << endl <<
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
                "    Running a benchmark with 1000 randomly generated floats using Quick Sort with pivot as a middle element:" << endl <<
                "      ./YourProject --test 3 1 1000 results.txt 2";
}