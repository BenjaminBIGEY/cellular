//
// Created by benji on 07/11/16.
//

#include <CImg/CImg.h> "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h" "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"  "pthread.h"

#include "Texture.h"

Texture Texture::load(std::string path) {

    //TODO Gérer le cas où on n'arrive pas à trouver l'image.

    cimg_library::CImg<unsigned char> image = cimg_library::CImg<>(path.c_str()).normalize(0, 255);
    int width = image.width();
    int height = image.height();
    unsigned char * pixels = new unsigned char[width * height * 3];

    for (int x = 0 ; x < width ; x++) {
        for (int y = 0 ; y < height ; y++) {
            pixels[(x * height + y) * 3] = image(y, x, 0);
            pixels[(x * height + y) * 3 + 1] = image(y, x, 1);
            pixels[(x * height + y) * 3 + 2] = image(y, x, 2);
        }
    }

    Texture result(width, height, pixels, GL_RGB, GL_RGB);

    delete[] pixels;

    return result;
}

Texture::Texture(int width, int height, const unsigned char* pixel, GLint internalFormat, GLenum format) {

    glGenTextures(1, &this->_id);
    glBindTexture(GL_TEXTURE_2D, this->_id);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixel);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    this->_instance_count = std::make_shared<int>(1);
}

Texture::Texture(const Texture &other) {
    this->_id = other._id;
    this->_instance_count = other._instance_count;

    *this->_instance_count += 1;
}

Texture::~Texture() {
    *this->_instance_count -= 1;

    if (*this->_instance_count ==0) {
        glDeleteTextures(1, &this->_id);
    }
}