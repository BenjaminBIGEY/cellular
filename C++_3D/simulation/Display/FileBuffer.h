//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_FILEBUFFER_H
#define LANGTON3D_FILEBUFFER_H


#include <string>
#include <vector>
#include <fstream>

class FileBuffer {
public :
    FileBuffer(std::string filename);

    void setFilename(std::string filename);
    std::string getFilename();
    void addLine(std::string line);

    void writeData();
private :
    std::string filename;
    std::vector<std::string> lines;
};


#endif //LANGTON3D_FILEBUFFER_H
