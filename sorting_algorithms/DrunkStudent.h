#ifndef DRUNKSTUDENT_H
#define DRUNKSTUDENT_H


template<typename T>
class DrunkStudent {
public:
    DrunkStudent();
    T* sort(T* data, int size);
    void sortingFile(char* filename, int distribution);
    void sortingTest(int iterations, int size, int distribution);

private:
    char* generateTimeResultsFilename(int size, int distribution);
    char* generateFilename(int size, int distribution, int nr);
    void heapify(T* data, int size, int i);
    void swap(T* a, T* b);
    void reverseArray(T* data, int size);
};



#endif //DRUNKSTUDENT_H
