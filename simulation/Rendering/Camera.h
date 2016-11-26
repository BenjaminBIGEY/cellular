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

/** Définit la caméra du rendu. */
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

    /** Fait tourner la caméra du nombre de degrés indiqué
     * vers la droite ou vers la gauche, autour du point central
     * de la vue. Le haut est donné par l'axe Z. */
    void rotateZ(float degrees);
    /** Fait tourner la caméra du nombre de degrés indiqué
     * vers le haut ou vers le bas, autour du point central
     * de la vue. Le haut est donné par l'axe Z.
     * La caméra ne peut s'orienter trop proche de l'axe Z.*/
    void rotateUpDown(float degrees);

    /** Zoome sur le point central de la vue, du facteur passé
     * en paramètres. */
    void zoom(float factor);

    /** Déplace la caméra de sorte que son origine soit à la
     * position indiquée. Le déplacement dure le nombre de secondes
     * passé en paramètres. */
    void travelEye(float eyeX, float eyeY, float eyeZ, float seconds);
    void travelEye(glm::vec3 eyePosition, float seconds);

    /** Indique si la caméra est actuellement en cours de
     * déplacement. */
    bool isTraveling() {return this->_traveling != nullptr;};

    /** Définit le traveling passé en paramètres comme traveling
     * actuel de la caméra. Le traveling fait ensuite décrire
     * une trajectoire lisse à la caméra, jusqu'au point demandé.*/
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


/** La classe Traveling permet de déplacer la caméra de
 * manière lisse jusqu'à un point désiré. */
class Traveling {

public :
    Traveling(Camera &camera, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

    Traveling(Camera &camera, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ) :
            Traveling(camera, eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0, 0, 1) { }

    /** Définit la durée du traveling, en secondes. */
    void setDuration(float duration);
    bool isFinished() {return this->_finished;};

    /** Méthode généralement appellée à la fin du traveling pour
     * s'assurer que la camera est bien à sa position finale.*/
    void applyImmediatly(Camera &camera);

    /** Cette méthode met à jour la position de la caméra, selon
     * ce traveling.*/
    void update(Camera &camera);

private :
    //Valeurs au début du traveling
    float _startEyeX, _startEyeY, _startEyeZ;
    float _startCenterX, _startCenterY, _startCenterZ;
    float _startUpX, _startUpY, _startUpZ;

    //Valeurs à atteindre
    float _eyeX, _eyeY, _eyeZ;
    float _centerX, _centerY, _centerZ;
    float _upX, _upY, _upZ;

    ///L'instant où le traveling débute en clicks.
    std::chrono::time_point<std::chrono::system_clock> _timeStarted;
    ///Durée du traveling de la caméra en secondes.
    float _duration = 0.5;
    bool _finished = false;
};


#endif //LANGTON3D_CAMERA_H
