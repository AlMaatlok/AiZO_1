#ifndef DRUNKSTUDENT_H
#define DRUNKSTUDENT_H


template<typename T>
class DrunkStudent {
public:
    DrunkStudent();
    T* sort(T* data, int size);
    void sorting_file(char* filename, int distribution);
    void sorting_test(int iterations, int size, int distribution);

private:
    char* generate_time_results_filename(int size, int distribution);
    char* generate_filename(int size, int distribution, int nr);
    void heapify(T* data, int size, int i);
    void swap(T* a, T* b);
    void reverseArray(T* data, int size);
};



#endif //DRUNKSTUDENT_H
