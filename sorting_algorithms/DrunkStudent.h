#ifndef DRUNKSTUDENT_H
#define DRUNKSTUDENT_H


template<typename T>
class DrunkStudent {
public:
    DrunkStudent();
    T* sort(T* data, int left, int right);
    void sorting_file(char* filename, int distribution);
    void sorting_test(int iterations, int size, int distribution);

private:
    int partition(T* data, int left, int right);
    char* generate_time_results_filename(int size, int distribution);
    char* generate_filename(int size, int distribution);
    void swap(T* a, T* b);
};



#endif //DRUNKSTUDENT_H
