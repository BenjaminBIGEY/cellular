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

////////////////////////////////////////////////////////////////////////////////////////////////////////////

Simulation::Simulation(PreConfiguredRules rules, float alpha) {
    // Scene creation
    _rules = std::make_shared<Rules>(rules);
    _grid = std::make_shared<Grid3D>(_rules->getListColors(), alpha);
    _scene = std::make_unique<Scene>(_grid);

    Light light;
    const glm::vec3 position[2] = {{10, 0, 0},
                                   {0,  0,  0}};

    glm::vec3 color(5, 5, 5); // strong white light
    //glm::vec3 color(0.4, 0.3, 0.1) // weak yellowish light
    GLfloat ambientCoeff = 0.06f; //0.2f or 1.0

    for(auto pos : position) {
        light.addLight(pos, color, ambientCoeff);
    }

    _scene->setLight(light);

    setEventListener(this);

    createWindow();
}

void Simulation::initialize() {
    std::cout << "Initialization of the simulation" << std::endl;
    _count = 0;
    _grid->reset(_rules->getListColors(), ALPHA_DEFAULT);

    _listAnts.clear();

    for(auto antInfos : _antsPosition) {
        Vector3 position = antInfos.first;
        Orientation orientation = antInfos.second;

        _grid->createCube(position);

        std::unique_ptr<Ant> ant = std::make_unique<Ant>(position, orientation);
        _listAnts.push_back(std::move(ant));
    }
}

void Simulation::setRules(int id) {
    if(id < PreConfiguredRules::NBR_RULES)
        setRules((PreConfiguredRules)id);
    else
        std::cout << "Rule don't implemented yet" << std::endl;
}

void Simulation::setRules(PreConfiguredRules rules) {
    _rules->loadPreConfiguredRule(rules);
    initialize();
}

void Simulation::addRule(std::string colorName, Move move) {
    _rules->add(colorName, move);
}

void Simulation::addRule(Color color, Move move) {
    _rules->add(color, move);
}

void Simulation::resetRules() {
    _rules->reset();
}

Simulation::~Simulation() {
    _listAnts.clear();
}

void Simulation::mainLoop() {
    if (!_pauseSimulation) {
        // Update of the simulation
        for (int i = 0; i < _listAnts.size(); i++) {
            Vector3 pos = _listAnts[i]->getPosition();
            _listAnts[i]->update(_grid->getColor(pos), _rules);

            _grid->update(pos, _rules);
        }
        _count++;
    }

    // Update of the display
    _window->setupFrame();

    if (!_pauseDisplaying) {
        if (!_scene->getCamera().isTraveling()) {
            _scene->render(_window->context());
            input();
        }
    }

    _window->finalizeFrame();
}

void Simulation::start() {
    _updateFrequency = DEFAULT_UPDATE_FREQUENCY;
    initialize();

    double beginLoop(0), endLoop(0), timeElapsed(0);

    _time1Update = 1.0 / _updateFrequency;

    while(_window->isWindowOpened()) {
        beginLoop = glfwGetTime();

        mainLoop();

        // Maintenance of the good FPS
        endLoop = glfwGetTime();
        timeElapsed = endLoop - beginLoop;
        if(timeElapsed < _time1Update)
            usleep((_time1Update - timeElapsed) * 1000000);
       // else
            //std::cerr << "FPS low : " << 1.0 / timeElapsed << '\n';
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

void Simulation::addAnt(int x, int y, int z, Orientation orientation) {
    addAnt(Vector3(x, y, z), orientation);
}

void Simulation::addAnt(Vector3 position, Orientation orientation) {
    _antsPosition.push_back(std::make_pair(position, orientation));
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
            _pauseSimulation = !_pauseSimulation;
        else if(key == GLFW_KEY_TAB)
            _pauseDisplaying = !_pauseDisplaying;
        else if(key == GLFW_KEY_ENTER)
            std::cout << "Time of simulation : " << _count << " steps." << std::endl;

            // TODO : add an interface to enter directly rules for simulation
        else if(key == GLFW_KEY_0) {
            std::cout << "Function don't implemented yet" << std::endl;
        } else if(key == GLFW_KEY_KP_1) {
            setRules(0);
        } else if(key == GLFW_KEY_KP_2) {
            setRules(1);
        } else if(key == GLFW_KEY_KP_3) {
            setRules(2);
        } else if(key == GLFW_KEY_KP_4) {
            setRules(3);
        } else if(key == GLFW_KEY_KP_5) {
            setRules(4);
        } else if(key == GLFW_KEY_KP_6) {
            setRules(5);
        } else if(key == GLFW_KEY_KP_7) {
            setRules(6);
        } else if(key == GLFW_KEY_KP_8) {
            setRules(7);
        } else if(key == GLFW_KEY_KP_9) {
            setRules(8);
        }

        else if(key == GLFW_KEY_N) {
            std::cout << "Composition of the grid : " << _grid->getSize() << " cubes.\n" << std::endl;
        }
        else if(key == GLFW_KEY_BACKSPACE) {
            initialize();
        }
        else if(key == GLFW_KEY_C) {
            if(_colored) {
                _colored = false;
                _window->context()->setCurrentProgram("lighted");
            } else {
                _colored = true;
                _window->context()->setCurrentProgram("colored");
            }
        }
        else if(key == GLFW_KEY_H) {
            std::cout << "\nCommands to control the 3D Langton Ant simulation :\n"
                    "[1->9] :      Load pre-configured rules\n"
                    "[Arrows] :    Orientate the camera\n"
                    "[BACKSPACE] : Reset the simulation\n"
                    "[ENTER] :     Get the time of the simulation (on ant steps)\n"
                    "[Escape] :    Quit\n"
                    "[SCROLL] :    Zoom\n"
                    "[SPACE] :     Pause the simulation\n"
                    "[TAB] :       Pause the displaying\n"
                    "C :           Switch between colored and lighted views\n"
                    "H :           Help message\n"
                    "N :           Get the number of cubes\n" << std::endl;
        }
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

void Simulation::setAlpha(float alpha) {
    _grid->setAlpha(alpha);
}