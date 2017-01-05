//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_CAMERA_H
#define LANGTON3D_CAMERA_H


#include <glm/glm.hpp>
#include <memory>
#include <ctime>
#include <chrono>

class Scene;
class Context;

class Traveling;

/// Create the render camera
class Camera {
public :
    Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) :
            _eyeX(eyeX), _eyeY(eyeY), _eyeZ(eyeZ), _centerX(centerX), _centerY(centerY), _centerZ(centerZ), _upX(upX), _upY(upY), _upZ(upZ) { }

    Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ) :
            Camera(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0, 0, 1) { }

    Camera() : Camera(4, 4, 4, 0, 0, 0, 0, 0, 1) { }

    void setFOV(float fov) {
        this->_fov = fov;
    }

    void setRatio(float ratio) {
        this->_ratio = ratio;
    }

    void setEye(float eyeX, float eyeY, float eyeZ);
    void setCenter(float centerX, float centerY, float centerZ);
    void setUp(float upX, float upY, float upZ);

    glm::vec3 getEye();
    glm::vec3 getCenter();
    glm::vec3 getUp();

    void moveCameraByCenterPoint(float newCenterX, float newCenterY, float newCenterZ);

    void rotateZ(float degrees);

    void rotateUpDown(float degrees);

    void zoom(float factor);

    void travelEye(float eyeX, float eyeY, float eyeZ, float seconds);
    void travelEye(glm::vec3 eyePosition, float seconds);

    bool isTraveling() {return this->_traveling != nullptr;};

    void traveling(std::unique_ptr<Traveling> & traveling);

    void updateCamera();
    void setCameraView(Context *context);

private:

    float _eyeX, _eyeY, _eyeZ;
    float _centerX, _centerY, _centerZ;
    float _upX, _upY, _upZ;

    float _fov = 60;
    float _ratio = 1;
    float _zNear = 0.1, _zFar = 1000;

    std::unique_ptr<Traveling> _traveling = nullptr;
};


class Traveling {

public :
    Traveling(Camera &camera, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

    Traveling(Camera &camera, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ) :
            Traveling(camera, eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0, 0, 1) { }

    void setDuration(float duration);
    bool isFinished() {return this->_finished;};

    void applyImmediatly(Camera &camera);

    void update(Camera &camera);

private :
    // Begin of traveling
    float _startEyeX, _startEyeY, _startEyeZ;
    float _startCenterX, _startCenterY, _startCenterZ;
    float _startUpX, _startUpY, _startUpZ;

    // End of traveling
    float _eyeX, _eyeY, _eyeZ;
    float _centerX, _centerY, _centerZ;
    float _upX, _upY, _upZ;

    std::chrono::time_point<std::chrono::system_clock> _timeStarted;

    float _duration = 0.5; // seconds
    bool _finished = false;
};


#endif //LANGTON3D_CAMERA_H
