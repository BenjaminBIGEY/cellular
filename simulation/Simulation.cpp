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

Simulation::Simulation(int ruleID) :
        Simulation(preConfiguredRules[ruleID <= PRE_CONFIGURED_RULES_NUMBER ? ruleID - 1 : 0]) {
    _currentPreConfiguredRules = ruleID <= PRE_CONFIGURED_RULES_NUMBER ? ruleID - 1 : 0;
}

Simulation::Simulation(RuleDefinition rules) {
    // Scene creation
    _rules = std::make_shared<Rules>(rules);
    _grid = std::make_shared<Grid3D>();
    _scene = std::make_unique<Scene>(_grid);

    Light light;
    const glm::vec3 position[2] = {{10, 0, 0},
                                   {0,  0,  0}};

    glm::vec3 color(5, 5, 5); // strong white light
    //glm::vec3 color(0.4, 0.3, 0.1); // weak yellowish light
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
    _grid->reset(_rules->getListColors());

    _listAnts.clear();

    for(auto antInfos : _antsPosition) {
        Vector3 position = antInfos.first;
        Orientation orientation = antInfos.second;

        _grid->addCube(position, NULL_COLOR);

        std::unique_ptr<Ant> ant = std::make_unique<Ant>(position, orientation);
        _listAnts.push_back(std::move(ant));
    }
    _beginSimulation = glfwGetTime();
}

void Simulation::createRules() {
    _pauseSimulation = true;
    RuleDefinition rules;
    std::cout << "\nRules sandbox for the simulation.\n";

    bool continueGetRules = true;

    while(continueGetRules) {
        Color color;

        std::cout << std::endl;
        std::cout << "To add a rule, give one of the following color :\n";
        for(int i = 0 ; i < COLORS_NUMBER ; i++) {
            Color c((AllColors)i);
            std::cout << "'" << c.getColorName() << "' ";
        }
        std::cout << "\nOr write [end|exit|quit|stop] to quit" << std::endl;

        std::string userEntry;
        getline(cin, userEntry);
        cin.clear();

        if(userEntry == "end" || userEntry == "exit" || userEntry == "quit" || userEntry == "stop") {
            continueGetRules = false;
            emptyBuffer();
        } else if(color.setColor(userEntry)) { // The user gives a correct color
            bool moveCorrect = false;
            int move = -1;
            while (!moveCorrect) {
                std::cout << "\n1 : GO_FRONT  ;  2 : GO_BACK  ;  3 : GO_RIGHT  ;  4 : GO_LEFT  ;  5 : GO_UP  ;  6 : GO_DOWN  ;  7 : DO_NOTHING" << std::endl;
                emptyBuffer();

                cin >> move;
                cin.clear();

                if (move < 1 or move > 7) {
                    std::cerr << "Invalid integer." << std::endl;
                } else {
                    moveCorrect = true;
                }
                emptyBuffer();
            }
            rules.addRule(color, (Move) move);
        }
        emptyBuffer();
    }

    if(rules.size() > 0) {
        setRules(rules);
        _window->setTitle("Langton 3D - new rules");
    }
    _pauseSimulation = false;
}

void Simulation::setRules(int ruleID) {
    if (ruleID <= PRE_CONFIGURED_RULES_NUMBER) {
        _currentPreConfiguredRules = ruleID;
    } else {
        std::cerr << "Unexisting rule. Launching of the rule 1." << std::endl;
        _currentPreConfiguredRules = 1;
    }
    setRules(preConfiguredRules[_currentPreConfiguredRules - 1]);

    _window->setTitle("Langton 3D - rule n°" + to_string(_currentPreConfiguredRules));
}

void Simulation::setRules(RuleDefinition rules) {
    _rules->loadRule(rules);
    initialize();
}

Simulation::~Simulation() {
    _listAnts.clear();
}

void Simulation::mainLoop() {
    if (!_pauseSimulation) {
        // Update of the simulation
        for (int i = 0; i < _listAnts.size(); i++) {
            Vector3 pos = _listAnts[i]->getPosition();
            _grid->update(pos, _rules);

            _listAnts[i]->update(_grid->getColor(), _rules);
        }
        _count++;
    }

    // Stop the simulation if the ant diverges (one of the directions is more than a LIMIT)
    if(!_diverge)
        if (_grid->getMaxCoord() == LIMIT_SIMULATION) {
            _pauseSimulation = true;
            _diverge = true;
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
        //beginLoop = glfwGetTime();

        mainLoop();

        // Maintenance of the good FPS
        //endLoop = glfwGetTime();
        //timeElapsed = endLoop - beginLoop;
        //if(timeElapsed < _time1Update)
            //usleep((_time1Update - timeElapsed) * 1000000);
        //else
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
    _window = std::make_unique<Window>("Langton 3D");

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
        // Exit the simulation
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
            // Ants pause
        else if (key == GLFW_KEY_SPACE)
            _pauseSimulation = !_pauseSimulation;
            // Displaying pause
        else if (key == GLFW_KEY_TAB)
            _pauseDisplaying = !_pauseDisplaying;
            // Get simulation time (in ants steps)
        else if (key == GLFW_KEY_ENTER)
            std::cout << "Time of simulation : " << _count << " steps (since " << glfwGetTime() - _beginSimulation << " seconds)." << std::endl;
            // Access to the previous rule
        else if (key == GLFW_KEY_KP_SUBTRACT) {
            if (_currentPreConfiguredRules > 1)
                setRules(_currentPreConfiguredRules - 1);
            else
                setRules(PRE_CONFIGURED_RULES_NUMBER);
        }
            // Access to the next rule
        else if (key == GLFW_KEY_KP_ADD) {
            if (_currentPreConfiguredRules < PRE_CONFIGURED_RULES_NUMBER)
                setRules(_currentPreConfiguredRules + 1);
            else
                setRules(1);
        }
            // User creates its own rules
        else if (key == GLFW_KEY_KP_ENTER) {
            createRules();
        }
            // Get the composition of the grid TODO : display the number of each color cubes
        else if (key == GLFW_KEY_N) {
            std::cout << "Composition of the grid : " << _grid->getSize() << " cubes.\n" << std::endl;
        }
            // Reset the simulation
        else if (key == GLFW_KEY_BACKSPACE) {
            initialize();
        }
            // Swap between colored cubes and uniformed, lighted cubes // TODO : get a better light
        else if (key == GLFW_KEY_C) {
            if (_colored) {
                _colored = false;
                _window->context()->setCurrentProgram("lighted");
            } else {
                _colored = true;
                _window->context()->setCurrentProgram("colored");
            }
        } else if (key == GLFW_KEY_X) {
            _grid->checkEclatedView();
        }
            // Display an help message
        else if (key == GLFW_KEY_H) {
            printHelp();
        }
    }
}

void Simulation::printHelp() {
    std::cout << "\nCommands to control the 3D Langton Ant simulation :\n"
            "[Arrows]    : Orientate the camera\n"
            "[BACKSPACE] : Reset the simulation\n"
            "[ENTER]     : Get the time of the simulation (on ant steps)\n"
            "[ENTER-KP]  : Create our own rules\n"
            "[Escape]    : Quit\n"
            "[SCROLL]    : Zoom\n"
            "[SPACE]     : Pause the simulation\n"
            "[TAB]       : Pause the displaying\n"
            "+           : Load next pre-configured rule\n"
            "-           : Load previous pre-configured rule\n"
            "C           : Switch between colored and lighted views\n"
            "H           : Help message\n"
            "N           : Get the number of cubes\n"
            "X           : Eclate cubes" << std::endl;
}

void Simulation::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    _scene->getCamera().zoom((float) pow(1.2, - yoffset));
}

void Simulation::debug() {
    for(int x = -10 ; x < 10 ; x+=2) {
        for(int y = -10 ; y < 10 ; y+=2) {
            for(int z = -10 ; z < 10 ; z+=2) {
                _grid->addCube(Vector3(x, y, z), RED);
            }
        }
    }
}