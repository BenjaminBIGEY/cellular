//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_RENDERABLE_H
#define LANGTON3D_RENDERABLE_H


#include <glad/glad.h>

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

class Scene;
class Context;

class Renderable {
public :
    virtual ~Renderable();

    virtual void render(Context *context, glm::vec3 position) = 0;


protected :
    Renderable();

    virtual void deleteBuffers();
    /// Recrée les buffers de données ainsi que le VAO,
    /// puis bind le vertex Array pour préparer un envoi
    /// de données.
    virtual void regenerateBuffers();

    bool _compiled = false;
    GLuint _gVAO = 0;
};

class RenderableModel : public Renderable {

public :
    RenderableModel();
    ~RenderableModel();

protected :
    virtual void deleteBuffers();

    virtual void regenerateBuffers();

    // Fields

    GLuint _vertexBuffer = 0;
    GLuint _colorCoordBuffer = 0;
};


#endif //LANGTON3D_RENDERABLE_H
