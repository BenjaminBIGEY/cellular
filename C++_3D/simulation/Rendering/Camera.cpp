//
// Created by benji on 07/11/16.
//

#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <iostream>

#include "Camera.h"
#include "Scene.h"
#include "Context.h"
#include "Program.h"

//Traveling
Traveling::Traveling(Camera &camera, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) :
        _eyeX(eyeX), _eyeY(eyeY), _eyeZ(eyeZ), _centerX(centerX), _centerY(centerY), _centerZ(centerZ), _upX(upX), _upY(upY), _upZ(upZ) {

    _timeStarted = std::chrono::system_clock::now();

    auto startEye = camera.getEye();
    auto startCenter = camera.getCenter();
    auto startUp = camera.getUp();

    _startEyeX = startEye.x;
    _startEyeY = startEye.y;
    _startEyeZ = startEye.z;

    _startCenterX = startCenter.x;
    _startCenterY = startCenter.y;
    _startCenterZ = startCenter.z;

    _startUpX = startUp.x;
    _startUpY = startUp.y;
    _startUpZ = startUp.z;
}

void Traveling::setDuration(float duration) {
    this->_duration = duration;
}

void Traveling::applyImmediatly(Camera &camera) {
    camera.setEye(_eyeX, _eyeY, _eyeZ);
    camera.setCenter(_centerX, _centerY, _centerZ);
    camera.setUp(_upX, _upY, _upZ);
}

void Traveling::update(Camera &camera) {
    auto now = std::chrono::system_clock::now();
    auto timeElapsed = now - this->_timeStarted;

    float ratio = std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
                  / (float) 1000000.0 / this->_duration;

    if (ratio >= 1) this->_finished = true;
    else {
        camera.setEye(
                _startEyeX + (_eyeX - _startEyeX) * ratio,
                _startEyeY + (_eyeY - _startEyeY) * ratio,
                _startEyeZ + (_eyeZ - _startEyeZ) * ratio
        );

        camera.setCenter(
                _startCenterX + (_centerX - _startCenterX) * ratio,
                _startCenterY + (_centerY - _startCenterY) * ratio,
                _startCenterZ + (_centerZ - _startCenterZ) * ratio
        );

        camera.setUp(
                _startUpX + (_upX - _startUpX) * ratio,
                _startUpY + (_upY - _startUpY) * ratio,
                _startUpZ + (_upZ - _startUpZ) * ratio
        );
    }
}



void Camera::setEye(float eyeX, float eyeY, float eyeZ) {
    this->_eyeX = eyeX;
    this->_eyeY = eyeY;
    this->_eyeZ = eyeZ;
}

void Camera::setCenter(float centerX, float centerY, float centerZ) {
    this->_centerX = centerX;
    this->_centerY = centerY;
    this->_centerZ = centerZ;
}

void Camera::setUp(float upX, float upY, float upZ) {
    this->_upX = upX;
    this->_upY = upY;
    this->_upZ = upZ;
}

glm::vec3 Camera::getEye() {
    return glm::vec3(_eyeX, _eyeY, _eyeZ);
}

glm::vec3 Camera::getCenter() {
    return glm::vec3(_centerX, _centerY, _centerZ);
}

glm::vec3 Camera::getUp() {
    return glm::vec3(_upX, _upY, _upZ);
}

void Camera::moveCameraByCenterPoint(float newCenterX, float newCenterY, float newCenterZ) {
    const float moveX = newCenterX - this->_centerX;
    const float moveY = newCenterY - this->_centerY;
    const float moveZ = newCenterZ - this->_centerZ;

    this->_eyeX += moveX;
    this->_eyeY += moveY;
    this->_eyeZ += moveZ;

    this->_centerX = newCenterX;
    this->_centerY = newCenterY;
    this->_centerZ = newCenterZ;
}

void Camera::rotateZ(float degrees) {
    const double radians = (float) (degrees * (M_PI / 180.0));
    const double c = cos(radians);
    const double s = sin(radians);

    const double diffX = this->_eyeX - this->_centerX;
    const double diffY = this->_eyeY - this->_centerY;

    this->_eyeX = (float) (diffX * c - diffY * s + this->_centerX);
    this->_eyeY = (float) (diffX * s + diffY * c + this->_centerY);
}

void Camera::rotateUpDown(float degrees) {
    const double radians = (float) (degrees * (M_PI / 180.0));
    const double c = cos(radians);
    const double s = sin(radians);

    const double diffX = this->_eyeX - this->_centerX;
    const double diffY = this->_eyeY - this->_centerY;
    const double diffZ = this->_eyeZ - this->_centerZ;

    const double radius = sqrt(diffX * diffX + diffY * diffY);
    const double radiusPrime = radius * c - diffZ * s;

    glm::vec3 newDiff(radiusPrime / radius * diffX, radiusPrime / radius * diffY, radius * s + diffZ * c);

    if (glm::abs(glm::dot(newDiff, getUp())) < glm::length(newDiff) * 0.99) {
        this->_eyeX = newDiff.x + this->_centerX;
        this->_eyeY = newDiff.y + this->_centerY;
        this->_eyeZ = newDiff.z + this->_centerZ;
    }
}

void Camera::zoom(float factor) {
    const double diffX = (this->_eyeX - this->_centerX) * factor;
    const double diffY = (this->_eyeY - this->_centerY) * factor;
    const double diffZ = (this->_eyeZ - this->_centerZ) * factor;

    if (diffX * diffX + diffY * diffY + diffZ * diffZ > 0.0001 || factor >= 1) {
        this->_eyeX = (float) (this->_centerX + diffX);
        this->_eyeY = (float) (this->_centerY + diffY);
        this->_eyeZ = (float) (this->_centerZ + diffZ);
    }
}

void Camera::travelEye(float eyeX, float eyeY, float eyeZ, float seconds) {
    auto traveling = std::make_unique<Traveling>(*this, eyeX, eyeY, eyeZ, _centerX, _centerY, _centerZ, _upX, _upY, _upZ);
    traveling->setDuration(seconds);
    this->traveling(traveling);
}

void Camera::traveling(std::unique_ptr<Traveling> &traveling) {
    this->_traveling = std::move(traveling);
}

void Camera::updateCamera() {
    if (this->_traveling == nullptr) return;

    if (this->_traveling->isFinished()) {
        this->_traveling->applyImmediatly(*this);
        this->_traveling = nullptr;
    }
    else {
        this->_traveling->update(*this);
    }
}

void Camera::setCameraView(Context *context) {
    //Frustum
    glm::mat4 projection = glm::perspective(glm::radians(_fov), _ratio, _zNear, _zFar);

    //Look at
    glm::mat4 camera = glm::lookAt(glm::vec3(_eyeX, _eyeY, _eyeZ), glm::vec3(_centerX, _centerY, _centerZ), glm::vec3(_upX, _upY, _upZ));

    if (context != nullptr) {
        context->program().setUniform3f((GLchar*)"cameraPosition", _eyeX, _eyeY, _eyeZ);
        context->program().setUniformMatrix4((GLchar*)"projection", projection);
        context->program().setUniformMatrix4((GLchar*)"camera", camera);
    }
}