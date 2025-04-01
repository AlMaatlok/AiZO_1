#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <string>

using namespace std;

template <typename T>
class FileHandler {
public:
    static int numberOfValues(const string& fileName);

    static T* readData(const string& fileName);

    static void writeData(const string& fileName, int count, const T* data);
};



#endif //FILEHANDLER_H
