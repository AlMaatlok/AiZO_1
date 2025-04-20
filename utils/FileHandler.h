#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <string>

using namespace std;

template <typename T>
class FileHandler {
public:
    static int numberOfValues(std::string& fileName);

    static T* readData(std::string& fileName);

    static void writeData(std::string& fileName, int count, const T* data);
};



#endif //FILEHANDLER_H
