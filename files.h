#ifndef FILES_H
#define FILES_H

#include <fstream>
using namespace std;

int countRecords(const char* filename, int recordSize)
{
    ifstream file(filename, ios::binary);

    if (!file)
        return 0;

    file.seekg(0, ios::end);
    int size = file.tellg();
    file.close();

    return size / recordSize;
}

#endif
