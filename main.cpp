
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include "sorting_algorithms/DrunkStudent.h"
#include "sorting_algorithms/HeapSort.h"
#include "sorting_algorithms/InsertionSort.h"
#include "sorting_algorithms/QuickSort.h"
#include "sorting_algorithms/ShellSort.h"
#include "utils/NumberGenerator.h"

using namespace std;
using namespace chrono;

//function to display help message
void helpMode();

int main(int cntArguments, char** args) {

    //check if the number of arguments is less than 6, then show help
    if (cntArguments < 6) {
        helpMode();
        return -1;
    }

    //parse input arguments
    std::string mode = args[1];         //mode: --file, --test or --help
    int sortingType = atoi(args[2]);    //sorting algorithm type (0 - Shell, 1 - Heap, 2 - Insertion, 3 - Quick, 4 - Drunk Student)
    int dataType = atoi(args[3]);       //data type (0 - int, 1 - float, 2 - double)
    int distribution = atoi(args[5]);   //initial distribution of data (-1 - descending, 0 - random, 1 - ascending, 3 - 33% sorted, 6 - 66% sorted)
    int extraArg = atoi(args[6]);       //extra argument for specific algorithm behavior

    //if mode is--file, process the file input
    if (mode == "--file") {
        cout << "File mode" << endl;
        char* filename = args[4];      //input file containing the data to be sorted


        //Shell Sort
        if (sortingType == 0) {
            if (dataType == 0) {
                if (extraArg == 0) {
                    ShellSort<int> shell_sort;
                    shell_sort.sortingFile(filename, ShellSort<int>::SHELL, distribution);
                }
                else if (extraArg == 1) {
                    ShellSort<int> shell_sort;
                    shell_sort.sortingFile(filename, ShellSort<int>::HIBBARD, distribution);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<int> shell_sort;
                    shell_sort.sortingFile(filename, ShellSort<int>::SHELL, distribution);
                }
            }
            else if (dataType == 1) {
                if (extraArg == 0) {
                    ShellSort<float> shell_sort;
                    shell_sort.sortingFile(filename, ShellSort<float>::SHELL, distribution);
                }
                else if (extraArg == 1) {
                    ShellSort<float> shell_sort;
                    shell_sort.sortingFile(filename, ShellSort<float>::HIBBARD, distribution);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<float> shell_sort;
                    shell_sort.sortingFile(filename, ShellSort<float>::SHELL, distribution);
                }
            }
            else if (dataType == 2) {
                if (extraArg == 0) {
                    ShellSort<double> shell_sort;
                    shell_sort.sortingFile(filename, ShellSort<double>::SHELL, distribution);
                }
                else if (extraArg == 1) {
                    ShellSort<double> shell_sort;
                    shell_sort.sortingFile(filename, ShellSort<double>::HIBBARD, distribution);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<double> shell_sort;
                    shell_sort.sortingFile(filename, ShellSort<double>::SHELL, distribution);
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
                heap_sort.sortingFile(filename, distribution);
            }
            else if (dataType == 1) {
                HeapSort<float> heap_sort;
                heap_sort.sortingFile(filename, distribution);
            }
            else if (dataType == 2) {
                HeapSort<double> heap_sort;
                heap_sort.sortingFile(filename, distribution);
            }
            else {
                cout << "Invalid argument for data type" << endl;
            }
        }

        //Insrtion Sort
        else if (sortingType == 2) {
            if (dataType == 0) {
                InsertionSort<int> insertion_sort;
                insertion_sort.sortingFile(filename, distribution);
            }
            else if (dataType == 1) {
                InsertionSort<float> insertion_sort;
                insertion_sort.sortingFile(filename, distribution);
            }
            else if (dataType == 2) {
                InsertionSort<double> insertion_sort;
                insertion_sort.sortingFile(filename, distribution);
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
                    quick_sort.sortingFile(filename, QuickSort<int>::FIRST, distribution);
                }
                else if (extraArg == 1) {
                    QuickSort<int> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<int>::LAST, distribution);
                }
                else if (extraArg == 2) {
                    QuickSort<int> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<int>::MIDDLE, distribution);
                }
                else if (extraArg == 3) {
                    QuickSort<int> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<int>::RANDOM, distribution);
                }
                else {
                    QuickSort<int> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<int>::MIDDLE, distribution);
                }
            }
            else if (dataType == 1) {
                if (extraArg == 0) {
                    QuickSort<float> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<float>::FIRST, distribution);
                }
                else if (extraArg == 1) {
                    QuickSort<float> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<float>::LAST, distribution);
                }
                else if (extraArg == 2) {
                    QuickSort<float> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<float>::MIDDLE, distribution);
                }
                else if (extraArg == 3) {
                    QuickSort<float> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<float>::RANDOM, distribution);
                }
                else {
                    QuickSort<float> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<float>::MIDDLE, distribution);
                }
            }
            else if (dataType == 2) {
                if (extraArg == 0) {
                    QuickSort<double> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<double>::FIRST, distribution);
                }
                else if (extraArg == 1) {
                    QuickSort<double> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<double>::LAST, distribution);
                }
                else if (extraArg == 2) {
                    QuickSort<double> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<double>::MIDDLE, distribution);
                }
                else if (extraArg == 3) {
                    QuickSort<double> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<double>::RANDOM, distribution);
                }
                else {
                    QuickSort<double> quick_sort;
                    quick_sort.sortingFile(filename, QuickSort<double>::MIDDLE, distribution);
                }
            }
        }
        else if (sortingType == 4) {
            if (dataType == 0) {
                DrunkStudent<int> drunkStudent;
                drunkStudent.sortingFile(filename, distribution);
            }
            else if (dataType == 1) {
                DrunkStudent<float> drunkStudent;
                drunkStudent.sortingFile(filename, distribution);
            }
            else if (dataType == 2) {
                DrunkStudent<double> drunkStudent;
                drunkStudent.sortingFile(filename, distribution);
            }
            else {
                cout << "Invalid argument for data type" << endl;
            }
        }
        else {
            cout << "Error!" << endl <<
                    "Argument for type of sorting must be from 0 to 4" << endl;
            helpMode();

            return -2;
        }
    }

    //id mode is --test, run test
    else if (mode == "--test") {
        cout << "test";
        int number_of_tests = 100;      //number of test to be performed
        int number_of_data = atoi(args[4]);   //size of the array to be generated and sorted

        //Shell Sort
        if (sortingType == 0) {
            if (dataType == 0) {
                if (extraArg == 0) {
                    ShellSort<int> shell_sort;
                    shell_sort.sortingTest(number_of_tests, number_of_data, ShellSort<int>::SHELL, distribution);
                }
                else if (extraArg == 1) {
                    ShellSort<int> shell_sort;
                    shell_sort.sortingTest(number_of_tests, number_of_data, ShellSort<int>::HIBBARD, distribution);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<int> shell_sort;
                    shell_sort.sortingTest(number_of_tests, number_of_data, ShellSort<int>::SHELL, distribution);
                }
            }
            else if (dataType == 1) {
                if (extraArg == 0) {
                    ShellSort<float> shell_sort;
                    shell_sort.sortingTest(number_of_tests, number_of_data, ShellSort<float>::SHELL, distribution);
                }
                else if (extraArg == 1) {
                    ShellSort<float> shell_sort;
                    shell_sort.sortingTest(number_of_tests, number_of_data, ShellSort<float>::HIBBARD, distribution);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<float> shell_sort;
                    shell_sort.sortingTest(number_of_tests, number_of_data, ShellSort<float>::SHELL, distribution);
                }
            }
            else if (dataType == 2) {
                if (extraArg == 0) {
                    ShellSort<double> shell_sort;
                    shell_sort.sortingTest(number_of_tests, number_of_data, ShellSort<double>::SHELL,distribution);
                }
                else if (extraArg == 1) {
                    ShellSort<double> shell_sort;
                    shell_sort.sortingTest(number_of_tests, number_of_data, ShellSort<double>::HIBBARD, distribution);
                }
                else {
                    cout << "Using default: SHELL gap" << endl;
                    ShellSort<double> shell_sort;
                    shell_sort.sortingTest(number_of_tests, number_of_data, ShellSort<double>::SHELL, distribution);
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
                heap_sort.sortingTest(number_of_tests, number_of_data, distribution);
            }
            else if (dataType == 1) {
                HeapSort<float> heap_sort;
                heap_sort.sortingTest(number_of_tests, number_of_data, distribution);
            }
            else if (dataType == 2) {
                HeapSort<double> heap_sort;
                heap_sort.sortingTest(number_of_tests, number_of_data, distribution);
            }
            else {
                cout << "Wrong argument for data type!" << endl;
            }
        }

        //Insrtion Sort
        else if (sortingType == 2) {
            if (dataType == 0) {
                InsertionSort<int> insertion_sort;
                insertion_sort.sortingTest(number_of_tests, number_of_data, distribution);
            }
            else if (dataType == 1) {
                InsertionSort<float> insertion_sort;
                insertion_sort.sortingTest(number_of_tests, number_of_data, distribution);
            }
            else if (dataType == 2) {
                InsertionSort<double> insertion_sort;
                insertion_sort.sortingTest(number_of_tests, number_of_data, distribution);
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
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<int>::FIRST, distribution);
                }
                else if (extraArg == 1) {
                    QuickSort<int> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<int>::LAST, distribution);
                }
                else if (extraArg == 2) {
                    QuickSort<int> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<int>::MIDDLE, distribution);
                }
                else if (extraArg == 3) {
                    QuickSort<int> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<int>::RANDOM, distribution);
                }
                else {
                    cout << "Default argument for pivot: MIDDLE" << endl;
                    QuickSort<int> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<int>::MIDDLE, distribution);
                }
            }
            else if (dataType == 1) {
                if (extraArg == 0) {
                    QuickSort<float> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<float>::FIRST, distribution);
                }
                else if (extraArg == 1) {
                    QuickSort<float> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<float>::LAST, distribution);
                }
                else if (extraArg == 2) {
                    QuickSort<float> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<float>::MIDDLE, distribution);
                }
                else if (extraArg == 3) {
                    QuickSort<float> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<float>::RANDOM, distribution);
                }
                else {
                    cout << "Default argument for pivot: MIDDLE" << endl;
                    QuickSort<float> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<float>::MIDDLE,  distribution);
                }
            }
            else if (dataType == 2) {
                if (extraArg == 0) {
                    QuickSort<double> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<double>::FIRST, distribution);
                }
                else if (extraArg == 1) {
                    QuickSort<double> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<double>::LAST, distribution);
                }
                else if (extraArg == 2) {
                    QuickSort<double> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<double>::MIDDLE, distribution);
                }
                else if (extraArg == 3) {
                    QuickSort<double> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<double>::RANDOM, distribution);
                }
                else {
                    cout << "Default argument for pivot: MIDDLE" << endl;
                    QuickSort<double> quick_sort;
                    quick_sort.sortingTest(number_of_tests, number_of_data, QuickSort<double>::MIDDLE,distribution);
                }
            }
            else {
                cout << "Wrong argument for data type!" << endl;
            }
        }
        else if (sortingType == 4) {
            if (dataType == 0) {
                DrunkStudent<int> drunk_student;
                drunk_student.sortingTest(number_of_tests, number_of_data, distribution);
            }
            else if (dataType == 1) {
                DrunkStudent<float> drunk_student;
                drunk_student.sortingTest(number_of_tests, number_of_data, distribution);
            }
            else if (dataType == 2) {
                DrunkStudent<double> drunk_student;
                drunk_student.sortingTest(number_of_tests, number_of_data, distribution);
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

    //if mode is --help, display help
    else if (mode == "--help") {
        helpMode();
    }
    else {
        cout << "Specify mode you would like to enter (file/test)" << endl;
        helpMode();
    }


    return 0;
}

//fun ction to display the help mode and instructions
void helpMode() {
    cout <<     "FILE TEST MODE:" << endl <<
                "   Usage:" << endl <<
                "    ./YourProject --file <algorithm> <type> <inputFile> <initial distribution> [pivot/gap] " << endl <<
                "   <algorithm> Sorting algorithm to use (0 - Shell, 1 - Heap, 2 - Insertion, 3 - Quick, 4 - Drunk Student)." << endl <<
                "   <type> Data type to load (0 - int, 1 - float, 2 - double)." << endl <<
                "   <inputFile> Input file containing the data to be sorted." << endl <<
                "   <initial distribution> How is the data sorted before the actual sorting (-1 - descending, 0 - random, 1 ascending, 3 - 33%, 6 - 66%)" << endl <<
                "   [pivot/gap] If provided, argument for pivot for Quick Sort (0 - first, 1 - last, 2 - middle, 3 - random)" << endl <<
                "               or for Shell Sort argument for gap (0 - Shell, 1 - Hibbard)" << endl <<
                endl <<
                "BENCHMARK MODE:" << endl <<
                "   Usage:" << endl <<
                "    ./YourProject --test <algorithm> <type> <size> <initial distribution> [pivot/gap]" << endl <<
                "   <algorithm> Sorting algorithm to use (0 - Shell, 1 - Heap, 2 - Insertion, 3 - Quick, 4 - Drunk Student)." << endl <<
                "   <type> Data type to generate (0 - int, 1 - float, 2 - double)." << endl <<
                "   <size> Number of elements to generate (instance size)." << endl <<
                "   <initial distribution> How is the data sorted before the actual sorting (-1 - descending, 0 - random, 1 ascending, 3 - 33%, 6 - 66%)" << endl <<
                "   [pivot/gap] If provided, argument for pivot for Quick Sort (0 - first, 1 - last, 2 - middle, 3 - random)" << endl <<
                "               or for Shell Sort argument for gap (0 - Shell, 1 - Hibbard)" << endl <<
                endl <<
                "HELP MODE:" << endl <<
                "   Usage:" << endl <<
                "    ./YourProject --help" << endl <<
                "   Displays this help message." << endl <<
                "   Notes:" << endl <<
                "   - The help message will also appear if no arguments are provides." << endl <<
                "   - Ensure that either --file or --test mode id specified;" << endl <<
                "     they are mutually exclusive." << endl <<
                "EXAMPLE CALLS:" << endl <<
                "    Sorting integers using Heap Sort from file and saving results:" << endl <<
                "      ./YourProject --file 1 0 input.txt sorted_output.txt" << endl <<
                endl <<
                "    Running a benchmark with 1000 randomly generated floats using Quick Sort with pivot as a middle element:" << endl <<
                "      ./YourProject --test 3 1 1000 results.txt 2";
}
