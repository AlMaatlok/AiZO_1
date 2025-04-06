#ifndef SORT_H
#define SORT_H



template <typename T>
class Sort {

public:
    Sort();
    Sort(T* data, int size);
    bool is_sorted(T* data, int size, bool asc);
    static T*  generate_random_array(int size);
    static T* generate_sorted_array(int size, float percentage_of_sorting, bool asc);
    T* sort(T* data, int size);
    void measure_sorting_from_file(T* data, int size);
    void measure_sorting_test(int iterations, int size);
    static void print_data(T* data, int size);


protected:
    T* not_sorted_data;
    T* data;
    int size;
};



#endif //SORT_H
