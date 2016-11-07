//
// Created by benji on 07/11/16.
//

#include "FileBuffer.h"

FileBuffer::FileBuffer(std::string filename) : filename(filename) {

}

void FileBuffer::addLine(std::string line) {
    this->lines.push_back(line);
}

void FileBuffer::setFilename(std::string filename) {
    this->filename = filename;
}

std::string FileBuffer::getFilename() {
    return this->filename;
}

void FileBuffer::writeData() {
    std::ofstream file(this->filename);

    for (auto &line : this->lines) {
        file << line << std::endl;
    }
    file.close();
}