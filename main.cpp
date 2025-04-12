#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include "sorting_algorithms/HeapSort.h"
#include "sorting_algorithms/InsertionSort.h"
#include "sorting_algorithms/QuickSort.h"
#include "sorting_algorithms/ShellSort.h"
#include "utils/NumberGenerator.h"

using namespace std;
using namespace chrono;

void helpMode();

int main(int cntArguments, char** args) {

    if (cntArguments < 5) {
        helpMode();
        return -1;
    }

    std::string mode = args[1];
    int sortingType = atoi(args[2]);
    int dataType = atoi(args[3]);
    int extraArg = atoi(args[5]);

    if (mode == "--file") {
        cout << "file";
        char* filename = args[4];


        //Shell Sort
        if (sortingType == 0) {
            if (dataType == 0) {
                if (extraArg == 0) {
                    ShellSort<int> shell_sort;
                    shell_sort.sorting_file(filename, ShellSort<int>::SHELL);
                }
                else if (extraArg == 1) {
                    ShellSort<int> shell_sort;
                    shell_sort.sorting_file(filename, ShellSort<int>::HIBBARD);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<int> shell_sort;
                    shell_sort.sorting_file(filename, ShellSort<int>::SHELL);
                }
            }
            else if (dataType == 1) {
                if (extraArg == 0) {
                    ShellSort<float> shell_sort;
                    shell_sort.sorting_file(filename, ShellSort<float>::SHELL);
                }
                else if (extraArg == 1) {
                    ShellSort<float> shell_sort;
                    shell_sort.sorting_file(filename, ShellSort<float>::HIBBARD);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<float> shell_sort;
                    shell_sort.sorting_file(filename, ShellSort<float>::SHELL);
                }
            }
            else if (dataType == 2) {
                if (extraArg == 0) {
                    ShellSort<double> shell_sort;
                    shell_sort.sorting_file(filename, ShellSort<double>::SHELL);
                }
                else if (extraArg == 1) {
                    ShellSort<double> shell_sort;
                    shell_sort.sorting_file(filename, ShellSort<double>::HIBBARD);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<double> shell_sort;
                    shell_sort.sorting_file(filename, ShellSort<double>::SHELL);
                }
            }
            else {
                cout << "Invalid argument for data type" << endl;
                helpMode();
            }
        }

        //Heap Sort
        else if (sortingType == 1) {
            if (dataType == 0) {
                HeapSort<int> heap_sort;
                heap_sort.sorting_file(filename);
            }
            else if (dataType == 1) {
                HeapSort<float> heap_sort;
                heap_sort.sorting_file(filename);
            }
            else if (dataType == 2) {
                HeapSort<double> heap_sort;
                heap_sort.sorting_file(filename);
            }
            else {
                cout << "Invalid argument for data type" << endl;
            }
        }

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
                cout << "Invalid argument for data type" << endl;
                helpMode();
            }
        }

        //Quick Sort
        else if (sortingType == 3) {
            if (dataType == 0) {
                if (extraArg == 0) {
                    QuickSort<int> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<int>::FIRST);
                }
                else if (extraArg == 1) {
                    QuickSort<int> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<int>::LAST);
                }
                else if (extraArg == 2) {
                    QuickSort<int> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<int>::MIDDLE);
                }
                else if (extraArg == 3) {
                    QuickSort<int> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<int>::RANDOM);
                }
                else {
                    QuickSort<int> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<int>::LAST);
                }
            }
            else if (dataType == 1) {
                if (extraArg == 0) {
                    QuickSort<float> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<float>::FIRST);
                }
                else if (extraArg == 1) {
                    QuickSort<float> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<float>::LAST);
                }
                else if (extraArg == 2) {
                    QuickSort<float> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<float>::MIDDLE);
                }
                else if (extraArg == 3) {
                    QuickSort<float> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<float>::RANDOM);
                }
                else {
                    QuickSort<float> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<float>::LAST);
                }
            }
            else if (dataType == 2) {
                if (extraArg == 0) {
                    QuickSort<double> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<double>::FIRST);
                }
                else if (extraArg == 1) {
                    QuickSort<double> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<double>::LAST);
                }
                else if (extraArg == 2) {
                    QuickSort<double> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<double>::MIDDLE);
                }
                else if (extraArg == 3) {
                    QuickSort<double> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<double>::RANDOM);
                }
                else {
                    QuickSort<double> quick_sort;
                    quick_sort.sorting_file(filename, QuickSort<double>::LAST);
                }
            }
        }
        else {
            cout << "Error!" << endl <<
                    "Argument for type of sorting must be from 0 to 3" << endl;
            helpMode();

            return -2;
        }
    }
    else if (mode == "--test") {
        cout << "test";
        int number_of_tests = 100;
        int number_of_data = atoi(args[4]);

        //Shell Sort
        if (sortingType == 0) {
            if (dataType == 0) {
                if (extraArg == 0) {
                    ShellSort<int> shell_sort;
                    shell_sort.sorting_test(number_of_tests, number_of_data, ShellSort<int>::SHELL);
                }
                else if (extraArg == 1) {
                    ShellSort<int> shell_sort;
                    shell_sort.sorting_test(number_of_tests, number_of_data, ShellSort<int>::HIBBARD);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<int> shell_sort;
                    shell_sort.sorting_test(number_of_tests, number_of_data, ShellSort<int>::SHELL);
                }
            }
            else if (dataType == 1) {
                if (extraArg == 0) {
                    ShellSort<float> shell_sort;
                    shell_sort.sorting_test(number_of_tests, number_of_data, ShellSort<float>::SHELL);
                }
                else if (extraArg == 1) {
                    ShellSort<float> shell_sort;
                    shell_sort.sorting_test(number_of_tests, number_of_data, ShellSort<float>::HIBBARD);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<float> shell_sort;
                    shell_sort.sorting_test(number_of_tests, number_of_data, ShellSort<float>::SHELL);
                }
            }
            else if (dataType == 2) {
                if (extraArg == 0) {
                    ShellSort<double> shell_sort;
                    shell_sort.sorting_test(number_of_tests, number_of_data, ShellSort<double>::SHELL);
                }
                else if (extraArg == 1) {
                    ShellSort<double> shell_sort;
                    shell_sort.sorting_test(number_of_tests, number_of_data, ShellSort<double>::HIBBARD);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<double> shell_sort;
                    shell_sort.sorting_test(number_of_tests, number_of_data, ShellSort<double>::SHELL);
                }
            }
            else {
                cout << "Invalid argument for data type" << endl;
                helpMode();
            }

        }

        //Heap Sort
        else if (sortingType == 1) {
            if (dataType == 0) {
                HeapSort<int> heap_sort;
                heap_sort.sorting_test(number_of_tests, number_of_data);
            }
            else if (dataType == 1) {
                HeapSort<float> heap_sort;
                heap_sort.sorting_test(number_of_tests, number_of_data);
            }
            else if (dataType == 2) {
                HeapSort<double> heap_sort;
                heap_sort.sorting_test(number_of_tests, number_of_data);
            }
            else {
                cout << "Wrong argument for data type!" << endl;
            }
        }

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
        else if (sortingType == 3) {
            if (dataType == 0) {
                if (extraArg == 0) {
                    QuickSort<int> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<int>::FIRST);
                }
                else if (extraArg == 1) {
                    QuickSort<int> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<int>::LAST);
                }
                else if (extraArg == 2) {
                    QuickSort<int> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<int>::MIDDLE);
                }
                else if (extraArg == 3) {
                    QuickSort<int> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<int>::RANDOM);
                }
                else {
                    cout << "Default argument for pivot: LAST" << endl;
                    QuickSort<int> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<int>::LAST);
                }
            }
            else if (dataType == 1) {
                if (extraArg == 0) {
                    QuickSort<float> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<float>::FIRST);
                }
                else if (extraArg == 1) {
                    QuickSort<float> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<float>::LAST);
                }
                else if (extraArg == 2) {
                    QuickSort<float> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<float>::MIDDLE);
                }
                else if (extraArg == 3) {
                    QuickSort<float> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<float>::RANDOM);
                }
                else {
                    cout << "Default argument for pivot: LAST" << endl;
                    QuickSort<float> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<float>::LAST);
                }
            }
            else if (dataType == 2) {
                if (extraArg == 0) {
                    QuickSort<double> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<double>::FIRST);
                }
                else if (extraArg == 1) {
                    QuickSort<double> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<double>::LAST);
                }
                else if (extraArg == 2) {
                    QuickSort<double> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<double>::MIDDLE);
                }
                else if (extraArg == 3) {
                    QuickSort<double> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<double>::RANDOM);
                }
                else {
                    cout << "Default argument for pivot: LAST" << endl;
                    QuickSort<double> quick_sort;
                    quick_sort.sorting_test(number_of_tests, number_of_data, QuickSort<double>::LAST);
                }
            }
            else {
                cout << "Wrong argument for data type!" << endl;
            }
        }

        else {
            cout << "Error!" << endl <<
                    "Argument for type of sorting must be from 0 to 3" << endl;
            helpMode();

            return -2;
        }
    }
    else if (mode == "--help") {
        helpMode();
    }
    else {
        cout << "Specify mode you would like to enter (file/test)" << endl;
        helpMode();
    }


    return 0;
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