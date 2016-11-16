//
// Created by benji on 08/11/16.
//

#include "Simulation.h"

void EventListener::init(Window * window) {
    window->setKeyCallback(glfwKeyCallback);
    window->setScrollCallback(glfwScrollCallback);
}

void EventListener::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    //for(int i = 0 ; i < getSizeListeners() ; i++) {
    //    _listListeners[i]->keyCallback(window, key, scancode, action, mods);
    for (auto &listener : _listListeners) {
        listener->keyCallback(window, key, scancode, action, mods);
    }
}

void EventListener::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    for (auto &listener : _listListeners) {
        listener->scrollCallback(window, xoffset, yoffset);
    }
}

Simulation::Simulation(int sizeX, int sizeY, int sizeZ, Color colorInit) {
    // Scene creation
    _grid = std::make_shared<Grid3D>(sizeX, sizeY, sizeZ, colorInit);
    _scene = std::make_unique<Scene>(_grid);

    Light light;
    const glm::vec3 position[2] = {/*{10, 10, 10},
                                  {0,  10, 10},
                                  {10, 0,  10},
                                  {10, 10, 0},
                                  {0,  0,  10},
                                  {0,  10, 0},*/
                                  {10, 0, 0},
                                  {0,  0,  0}};

    glm::vec3 color(5, 5, 5); // strong white light
    //glm::vec3 color(0.4, 0.3, 0.1) // weak yellowish light
    GLfloat ambientCoeff = 0.06f; //0.2f or 1.0

    for(auto pos : position) {
        light.addLight(pos, color, ambientCoeff);
    }

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

    if(cameraUp.x == 0 && cameraUp.y == 0) {
        /// Arrow keys
        if(_rightKey == GLFW_PRESS && _leftKey != GLFW_PRESS) {
            _scene->getCamera().rotateZ(180.0f / 70.0f);
        } else if(_leftKey == GLFW_PRESS && _rightKey != GLFW_PRESS) {
            _scene->getCamera().rotateZ(-180.0f / 70.0f);
        }

        if(_upKey == GLFW_PRESS && _downKey != GLFW_PRESS) {
            _scene->getCamera().rotateUpDown(180.0f / 70.0f);
        } else if(_downKey == GLFW_PRESS && _upKey != GLFW_PRESS) {
            _scene->getCamera().rotateUpDown(-180.0f / 70.0f);
        }

        /// Plus and Minus keys
        if(_plusKey == GLFW_PRESS && _minusKey != GLFW_PRESS) {
            _scene->getCamera().zoom(0.5f);
        } else if(_minusKey == GLFW_PRESS && _plusKey != GLFW_PRESS) {
            _scene->getCamera().zoom(-0.5f);
        }
    } else if(cameraUp.z == 0) {
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

    EventListener::init(_window.get());

    // Set the required callback functions
    //_window->setKeyCallback(EventListener::glfwKeyCallback);
    //_window->setScrollCallback(glfwScrollCallback);

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
void Simulation::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
        _scene->getCamera().rotateUpDown(50.0f);
        /*else if (key == GLFW_KEY_0) {
            auto traveling = std::make_unique<Traveling>(
                    _scene->getCamera(), 0, 0, 30, 0, 0, 0, 0, 1, 0
            );
            traveling->setDuration(0.5f);
            _scene->getCamera().traveling(traveling);
        }*/
    }
}

void Simulation::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    _scene->getCamera().zoom((float) pow(1.2, - yoffset));
}

void Simulation::setColor(int x, int y, int z, Color color) {
    _grid->setColor(x, y, z, color);
}