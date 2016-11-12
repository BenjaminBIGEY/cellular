//
// Created by benji on 08/11/16.
//

#include "Simulation.h"


Simulation::Simulation(int sizeX, int sizeY, int sizeZ, Color colorInit) {
    _grid = std::make_shared<Grid3D>(sizeX, sizeY, sizeZ, colorInit);
    _scene = std::make_shared<Scene>(_grid);

    Light light(LIGHT_POINT, 0, 0, 0);
    _scene->setLight(light);

    _window = std::make_unique<Window>();
    // Set the required callback functions
    _window->setKeyCallback(glfwKeyCallback);
    _window->setScrollCallback(glfwScrollCallback);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    createControlKeys();
}

Simulation::~Simulation() {
    _listAnts.clear();
}

void Simulation::mainLoop() {
    // Update of the simulation
    for(int i = 0 ; i < _listAnts.size() ; i++) {
        //for (auto ant : _listAnts) {
        Vector3 pos = _listAnts[i]->getPosition();
        _listAnts[i]->update(_grid->getColor(pos.x, pos.y, pos.z));

        _grid->update(pos);
    }
    _count++;

    // Update of the display
    _window->setupFrame();

    if (!_scene->getCamera().isTraveling()) {
        _scene->render(_window->context());
    }
    input();

    _window->finalizeFrame();
}

void Simulation::start(int fps) {
    double frameRate = 1000.0 / fps; // 1000 ms / frames per seconds
    double beginLoop(0), endLoop(0), timeElapsed(0);

    while(_window->isWindowOpened()) {
        beginLoop = glfwGetTime();

        mainLoop();

        endLoop = glfwGetTime();
        timeElapsed = endLoop - beginLoop;
        if(timeElapsed < frameRate)
            usleep(frameRate - timeElapsed);
    }
}


void Simulation::input() {
    glm::vec3 cameraUp = _scene->getCamera().getUp();

    if (cameraUp.x == 0 && cameraUp.y == 0) {
        if (_rightKey == GLFW_PRESS && _leftKey != GLFW_PRESS) {
            _scene->getCamera().rotateZ(180.0f / 70.0f);
        } else if (_leftKey == GLFW_PRESS && _rightKey != GLFW_PRESS) {
            _scene->getCamera().rotateZ(-180.0f / 70.0f);
        }

        if (_upKey == GLFW_PRESS && _downKey != GLFW_PRESS) {
            _scene->getCamera().rotateUpDown(180.0f / 70.0f);
        } else if (_downKey == GLFW_PRESS && _upKey != GLFW_PRESS) {
            _scene->getCamera().rotateUpDown(-180.0f / 70.0f);
        }
    }
}

void Simulation::addAnt(int x, int y, int z) {
    std::unique_ptr<Ant> ant = std::make_unique<Ant>(x, y, z, Orientation::FRONT);
    _listAnts.push_back(std::move(ant));
}

void Simulation::createControlKeys() {
    _rightKey = glfwGetKey(_window->window(), GLFW_KEY_RIGHT);
    _leftKey = glfwGetKey(_window->window(), GLFW_KEY_LEFT);
    _upKey = glfwGetKey(_window->window(), GLFW_KEY_UP);
    _downKey = glfwGetKey(_window->window(), GLFW_KEY_DOWN);
}

/*
 * Callbacks definition
 */
void Simulation::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
/*
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_KP_0) {
            auto traveling = std::make_unique<Traveling>(
                    _scene->getCamera(), 0, 0, 30, 0, 0, 0, 0, 1, 0
            );
            traveling->setDuration(0.5f);
            _scene->getCamera().traveling(traveling);
        }
        else if (key >= GLFW_KEY_KP_1 && key <= GLFW_KEY_KP_9){
            int targetPlanet = key - GLFW_KEY_KP_1;

            if (targetPlanet < planets.size()) {
                currentPlanet = targetPlanet;

                std::shared_ptr<Body> planetBody = planets[currentPlanet].body;

                //TODO le 15 en fonction du radius de la planète.

                auto traveling = std::make_unique<Traveling>(
                        scene->camera(),
                        planetBody->getX() + 15, planetBody->getY() + 15, planetBody->getZ() + 15,
                        planetBody->getX(), planetBody->getY(), planetBody->getZ(), 0, 0, 1
                );
                traveling->setDuration(0.5f);
                scene->camera().traveling(traveling);
            }
        }
    }*/
}

void Simulation::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    //_scene->getCamera().zoom((float) pow(1.2, - yoffset));
}