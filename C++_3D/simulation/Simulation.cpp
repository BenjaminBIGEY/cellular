//
// Created by benji on 08/11/16.
//

#include "Simulation.h"


Simulation::Simulation(int sizeX, int sizeY, int sizeZ, Color colorInit) {
    // Scene creation
    _grid = std::make_shared<Grid3D>(sizeX, sizeY, sizeZ, colorInit);
    _scene = std::make_unique<Scene>(_grid);

    Light light(10, 10, 10);
    _scene->setLight(light);
}

Simulation::~Simulation() {
    _listAnts.clear();
}

void Simulation::mainLoop() {
    // Update of the simulation
    for(int i = 0 ; i < _listAnts.size() ; i++) {
        glm::vec3 pos = _listAnts[i]->getPosition();
        _listAnts[i]->update(_grid->getColor(pos));

        _grid->update(pos, _count);
    }
    _count++;

    // Update of the display
    _window->setupFrame();


    if (!_scene->getCamera().isTraveling()) {
        _scene->render(_window->context());
        input();
    }


    _window->finalizeFrame();
}

void Simulation::start(int fps) {
    createWindow();

    double frameRate = 100.0 / fps; // 1000 ms / frames per seconds
    double beginLoop(0), endLoop(0), timeElapsed(0);

    while(_window->isWindowOpened()) {
        beginLoop = glfwGetTime();

        mainLoop();

        // Maintenance of the good FPS
        endLoop = glfwGetTime();
        timeElapsed = endLoop - beginLoop;
        if(timeElapsed < frameRate)
            usleep(frameRate - timeElapsed);
        else
            std::cerr << "FPS low : " << 1.0 / timeElapsed << '\n';
    }
}


void Simulation::input() {
    glm::vec3 cameraUp = _scene->getCamera().getUp();

    createControlKeys();

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
    } else if (cameraUp.z == 0) {
        // TODO
    }
}

void Simulation::addAnt(int x, int y, int z) {
    std::unique_ptr<Ant> ant;
    if(x > _grid->getSizeX() || y > _grid->getSizeY() || z > _grid->getSizeZ()) {
        std::cerr << "Init position of the ant out of range\n" << std::endl;
        ant = std::make_unique<Ant>(_grid->getSizeX() / 2, _grid->getSizeY() / 2, _grid->getSizeZ() / 2, Orientation::FRONT);
    } else
        ant = std::make_unique<Ant>(x, y, z, Orientation::FRONT);

    _listAnts.push_back(std::move(ant));
}

void Simulation::createWindow() {
    _window = std::make_unique<Window>();
    // Set the required callback functions
    _window->setKeyCallback(glfwKeyCallback);
    _window->setScrollCallback(glfwScrollCallback);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
        /*else if (key == GLFW_KEY_0) {
            auto traveling = std::make_unique<Traveling>(
                    _scene->getCamera(), 0, 0, 30, 0, 0, 0, 0, 1, 0
            );
            traveling->setDuration(0.5f);
            _scene->getCamera().traveling(traveling);
        }*/
    }
}

void Simulation::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    //_scene->getCamera().zoom((float) pow(1.2, - yoffset));
}