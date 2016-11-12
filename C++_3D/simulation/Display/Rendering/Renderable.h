//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_RENDERABLE_H
#define LANGTON3D_RENDERABLE_H


#include "Material.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

class Scene;
class Context;

class Renderable {
public :
    virtual ~Renderable();

    virtual void render(Context *context) = 0;


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

    void setPosition(float x, float y, float z);
    glm::vec3 getPosition();

    void setMaterial(Material &material);
    void addTexturePath(std::string path);

    Material & getMaterial() {
        return this->_material;
    }
protected :
    virtual void deleteBuffers();

    virtual void regenerateBuffers();

    /** Recharge les textures et envoie les données à
     * openGL*/
    virtual void loadTextures();

    //Fields

    float _x, _y, _z;
    Material _material;
    std::vector<std::string> _texturePaths;

    GLuint _vertexBuffer = 0;
    GLuint _normalBuffer = 0;
    GLuint _texCoordBuffer = 0;
};


#endif //LANGTON3D_RENDERABLE_H
