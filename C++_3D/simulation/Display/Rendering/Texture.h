//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_TEXTURE_H
#define LANGTON3D_TEXTURE_H


#include <glad/glad.h>
#include <memory>


class Texture {
public :
    static Texture load(std::string path);

    Texture(int width, int height, const unsigned char* pixel,
            GLint internalFormat = GL_RGBA, GLenum format = GL_RGBA);
    Texture(const Texture & other);
    ~Texture();

    GLuint getID() {return this->_id;}
private :
    GLuint _id = 0;
    std::shared_ptr<int> _instance_count;
};


#endif //LANGTON3D_TEXTURE_H
