//
// Created by benji on 08/11/16.
//

#include "Simulation.h"

EventListener* EventListener::listener = NULL;

void EventListener::init(Window * mainWindow) {
    EventListener::listener = this;

    mainWindow->setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
        EventListener::listener->glfwKeyCallback(window, key, scancode, action, mods);
    });

    mainWindow->setScrollCallback([](GLFWwindow* window, double xoffset, double yoffset) {
        EventListener::listener->glfwScrollCallback(window, xoffset, yoffset);
    });
}

void EventListener::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    listener->keyCallback(window, key, scancode, action, mods);
}

void EventListener::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    listener->scrollCallback(window, xoffset, yoffset);
}

void EventListener::setEventListener(EventListener* eventListener) {
    listener = eventListener;
}

Simulation::Simulation(Color colorInit, float alpha) {
    // Scene creation
    _grid = std::make_shared<Grid3D>(colorInit, alpha);
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

    //EventListener* event = this;
    setEventListener(this);
}

Simulation::~Simulation() {
    _listAnts.clear();
}

void Simulation::mainLoop() {
    if(!_pause) {
        // Update of the simulation
        for (int i = 0; i < _listAnts.size(); i++) {
            Vector3 pos = _listAnts[i]->getPosition();
            _listAnts[i]->update(_grid->getColor(pos));

            _grid->update(pos);
        }
        _count++;
    }

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
        /// Arrow keys : rotation control
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

        /// Plus and Minus keys : zoom control
        /*if(_plusKey == GLFW_PRESS && _minusKey != GLFW_PRESS) {
            _scene->getCamera().zoom(0.5f);
        } else if(_minusKey == GLFW_PRESS && _plusKey != GLFW_PRESS) {
            _scene->getCamera().zoom(-0.5f);
        }*/

        /// ZQSD keys : traveling control
        glm::vec3 eyePos = _scene->getCamera().getEye();
        float duration = 0.2f;
        if(_keyD == GLFW_PRESS && _keyQ != GLFW_PRESS) {
            _listAnts[0]->setOrientation(Orientation::RIGHT);
            //_scene->getCamera().travelEye((eyePos + glm::vec3(0, 1, 0)), duration);
        } else if(_keyQ == GLFW_PRESS && _keyD != GLFW_PRESS) {
            _listAnts[0]->setOrientation(Orientation::LEFT);
            //_scene->getCamera().travelEye((eyePos + glm::vec3(0, -1, 0)), duration);
        }

        if(_keyZ == GLFW_PRESS && _keyS != GLFW_PRESS) {
            _listAnts[0]->setOrientation(Orientation::UP);
            //_scene->getCamera().travelEye((eyePos + glm::vec3(1, 0, 0)), duration);
        } else if(_keyS == GLFW_PRESS && _keyZ != GLFW_PRESS) {
            _listAnts[0]->setOrientation(Orientation::DOWN);
            //_scene->getCamera().travelEye((eyePos + glm::vec3(-1, 0, 0)), duration);
        }

        if(_keyA == GLFW_PRESS && _keyE != GLFW_PRESS) {
            _listAnts[0]->setOrientation(Orientation::FRONT);
            //_scene->getCamera().travelEye((eyePos + glm::vec3(0, 0, 1)), duration);
        } else if(_keyE == GLFW_PRESS && _keyA != GLFW_PRESS) {
            _listAnts[0]->setOrientation(Orientation::BACK);
            //_scene->getCamera().travelEye((eyePos + glm::vec3(0, 0, -1)), duration);
        }

    } else if(cameraUp.z == 0) {
        // TODO
    }
}

void Simulation::addAnt(int x, int y, int z) {
    addAnt(Vector3(x, y, z));
}

void Simulation::addAnt(Vector3 position) {
    _grid->createCube(position);

    std::unique_ptr<Ant> ant = std::make_unique<Ant>(position, Orientation::FRONT);
    _listAnts.push_back(std::move(ant));
}

void Simulation::createWindow() {
    _window = std::make_unique<Window>();

    EventListener::init(_window.get());



    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Simulation::createControlKeys() {
    /// Rotation control
    _rightKey = glfwGetKey(_window->window(), GLFW_KEY_RIGHT);
    _leftKey  = glfwGetKey(_window->window(), GLFW_KEY_LEFT);
    _upKey    = glfwGetKey(_window->window(), GLFW_KEY_UP);
    _downKey  = glfwGetKey(_window->window(), GLFW_KEY_DOWN);

    /// Zoom control
    //_plusKey = glfwGetKey(_window->window(), GLFW_KEY_PLUS);
    //_minusKey = glfwGetKey(_window->window(), GLFW_KEY_MINUS);

    /// Traveling control
    _keyA = glfwGetKey(_window->window(), GLFW_KEY_A);
    _keyZ = glfwGetKey(_window->window(), GLFW_KEY_Z);
    _keyE = glfwGetKey(_window->window(), GLFW_KEY_E);
    _keyQ = glfwGetKey(_window->window(), GLFW_KEY_Q);
    _keyS = glfwGetKey(_window->window(), GLFW_KEY_S);
    _keyD = glfwGetKey(_window->window(), GLFW_KEY_D);
}

/*
 * Callbacks definition
 */
void Simulation::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    if(action == GLFW_PRESS) {
        if(key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
        else if(key == GLFW_KEY_SPACE)
            _pause = !_pause;
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
    setColor(Vector3(x, y, z), color);
}

void Simulation::setColor(Vector3 position, Color color) {
    _grid->setColor(position, color);
}

void Simulation::setAlpha(Color color) {
    _grid->setAlpha(color, ALPHA_DEFAULT);
}