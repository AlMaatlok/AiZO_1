#include "Sort.h"

#include <chrono>
#include <ctime>
#include <iosfwd>
#include <string.h>
#include <ctime>
#include <sstream>
#include <string>
#include <typeinfo>
#include <chrono>

using namespace std;
using namespace chrono;

template <typename T>
Sort<T>::Sort() {
}
//Function to check if data is fully sorted
template <typename T>
bool Sort<T>::is_sorted(T* data, int size) {

    for (int i = 1; i < size; i++) {
        if (data[i - 1] > data[i]) {
            return false;
        }
    }
    return true;
}


//Function to sort an array for test number 2
template<typename T>
T* Sort<T>::sort_array_for_test2(T* data, int size, float percentage_of_sorting, bool ascending) {

    float size_of_sorted_array = static_cast<float>(size) * percentage_of_sorting;

    for (int i = 0; i < size_of_sorted_array; i++){
        for (int j = 0; j < size - 1; j++){
            if ((ascending && data[j] > data[j + 1]) || (!ascending && data[j] < data[j + 1]))
            {
                T temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
    return data;
}

template <typename T>
void Sort<T>::sorting_test(int iterations, int size) {

    //char* filename =generate_time_results_filename();

    /*double avg_duration = 0;

    // tyle razy ile zadano, sortuj i zmierz czas
    for (int _ = 0; _ < no_times; _++) {
        T* ptr = this->generate_random_array(size);
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        this->sort(ptr, size);
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

        double sort_duration = chrono::duration_cast<chrono::duration<double>>(t2 - t1).count();
        cout << "sorting took: " << sort_duration << "s" << endl;
        avg_duration += sort_duration;
    }

    cout << "average sorting time: " << avg_duration / no_times << "s" << endl;*/
}
template <typename T>
char* Sort<T>::generate_time_results_filename(char** sorting) {
    const auto now = system_clock::now();
    const time_t timeNow = system_clock::to_time_t(now);

    const tm* timeInfo = localtime(&timeNow);

    stringstream filename;
    filename << sorting << "-"
             << typeid(T).name() << "-"
             << (timeInfo->tm_year + 1900) << "-"
             << (timeInfo->tm_mon + 1) << "-"
             << (timeInfo->tm_mday) << "-"
             << (timeInfo->tm_hour) << "."
             << (timeInfo->tm_min) << ".csv";

    // Alokujemy pamięć dynamicznie i kopiujemy string
    std::string s = filename.str();
    char* result = new char[s.length() + 1];
    strcpy(result, s.c_str());

    return result;
}



template class Sort<int>;
template class Sort<float>;
template class Sort<double>;
