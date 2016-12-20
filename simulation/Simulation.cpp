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
    std::cout << _BOLD(_MAGENTA("Initialization of the simulation")) << std::endl;
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
    if(_antsPosition.size() > 0) {
        Vector3 posAnt = _antsPosition[0].first;
        _scene->getCamera().moveCameraByCenterPoint(posAnt.x, posAnt.y, posAnt.z);
        _scene->getCamera().setCenter(posAnt.x * 2, posAnt.y * 2, posAnt.z * 2);
        _scene->getCamera().setEye(posAnt.x * 5, posAnt.y * 5, posAnt.z * 5);
        _scene->getCamera().zoom(0.01f);
    }

    // Disable the 60 FPS limit
    glfwSwapInterval(0);

    _beginSimulation = glfwGetTime();
}

void Simulation::createRules() {
    pauseSimulation(true);
    RuleDefinition rules;
    std::cout << _UNDL(_BOLD(_BLUE("\nRules sandbox for the simulation :\n")));

    bool continueGetRules = true;

    while(continueGetRules) {
        Color color;

        std::cout << std::endl;
        std::cout << _CYAN("To add a rule, give one of the following color :\n");
        for(int i = 0 ; i < COLORS_NUMBER ; i++) {
            Color c((AllColors)i);
            std::cout << "'" << c.getColorName() << "' ";
        }
        std::cout << _GREEN("\nOr write [end|exit|quit|stop] to quit") << std::endl;

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
    pauseSimulation(false);
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
    /*if(!_diverge)
        if (_grid->getMaxCoord() == LIMIT_SIMULATION) {
            pauseSimulation(true);
            _diverge = true;
        }*/
    /*if(_count == 386)
        pauseSimulation(true);*/

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
    std::cout << _BOLD(_MAGENTA("\nEnd of the simulation")) << std::endl;
}

void Simulation::pauseSimulation(bool desactivate) {
    // pausing
    if(!_pauseSimulation and desactivate) {
        _pauseSimulation = true;
        _beginSimulationPaused = glfwGetTime();
    }
    // already paused : relaunch
    else if(_pauseSimulation and !desactivate) {
        _pauseSimulation = false;
        _beginSimulation += glfwGetTime() - _beginSimulationPaused;
    }
}


void Simulation::input() {
    glm::vec3 cameraUp = _scene->getCamera().getUp();

    createControlKeys();

    if(cameraUp.x == 0 && cameraUp.y == 0) {
        /// Arrow keys : rotation control
        if(_rightKey == GLFW_PRESS && _leftKey != GLFW_PRESS) {
            _scene->getCamera().rotateZ(0.8f);
        } else if(_leftKey == GLFW_PRESS && _rightKey != GLFW_PRESS) {
            _scene->getCamera().rotateZ(-0.8f);
        }

        if(_upKey == GLFW_PRESS && _downKey != GLFW_PRESS) {
            _scene->getCamera().rotateUpDown(0.8f);
        } else if(_downKey == GLFW_PRESS && _upKey != GLFW_PRESS) {
            _scene->getCamera().rotateUpDown(-0.8f);
        }

        /// ZQSD keys : traveling control
        glm::vec3 eyePos = _scene->getCamera().getEye();
        float duration = 0.2f;
        if(_keyD == GLFW_PRESS && _keyQ != GLFW_PRESS) {
            glm::vec3 center = _scene->getCamera().getCenter();
            _scene->getCamera().setCenter(center.x, center.y + 0.5f, center.z);
            glm::vec3 eye = _scene->getCamera().getEye();
            _scene->getCamera().setEye(eye.x, eye.y + 0.5f, eye.z);
        } else if(_keyQ == GLFW_PRESS && _keyD != GLFW_PRESS) {
            glm::vec3 center = _scene->getCamera().getCenter();
            _scene->getCamera().setCenter(center.x, center.y - 0.5f, center.z);
            glm::vec3 eye = _scene->getCamera().getEye();
            _scene->getCamera().setEye(eye.x, eye.y - 0.5f, eye.z);
        }

        if(_keyZ == GLFW_PRESS && _keyS != GLFW_PRESS) {
            glm::vec3 center = _scene->getCamera().getCenter();
            _scene->getCamera().setCenter(center.x + 0.5f, center.y, center.z);
            glm::vec3 eye = _scene->getCamera().getEye();
            _scene->getCamera().setEye(eye.x + 0.5f, eye.y, eye.z);
        } else if(_keyS == GLFW_PRESS && _keyZ != GLFW_PRESS) {
            glm::vec3 center = _scene->getCamera().getCenter();
            _scene->getCamera().setCenter(center.x - 0.5f, center.y, center.z);
            glm::vec3 eye = _scene->getCamera().getEye();
            _scene->getCamera().setEye(eye.x - 0.5f, eye.y, eye.z);
        }

        if(_keyA == GLFW_PRESS && _keyE != GLFW_PRESS) {
            glm::vec3 center = _scene->getCamera().getCenter();
            _scene->getCamera().setCenter(center.x, center.y, center.z + 0.5f);
            glm::vec3 eye = _scene->getCamera().getEye();
            _scene->getCamera().setEye(eye.x, eye.y, eye.z + 0.5f);
        } else if(_keyE == GLFW_PRESS && _keyA != GLFW_PRESS) {
            glm::vec3 center = _scene->getCamera().getCenter();
            _scene->getCamera().setCenter(center.x, center.y, center.z - 0.5f);
            glm::vec3 eye = _scene->getCamera().getEye();
            _scene->getCamera().setEye(eye.x, eye.y, eye.z - 0.5f);
        }

    } else if(cameraUp.z == 0) {
        // TODO
    }
}

void Simulation::addAnt(int x, int y, int z, Orientation orientation) {
    addAnt(Vector3(x, y, z), orientation);
}

void Simulation::addAnt(Vector3 position, Orientation orientation) {
    Vector3 pos = position;
    pos += Vector3(500, 500, 500);
    _antsPosition.push_back(std::make_pair(pos, orientation));
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
    _keyA = glfwGetKey(_window->window(), GLFW_KEY_Q);
    _keyZ = glfwGetKey(_window->window(), GLFW_KEY_W);
    _keyE = glfwGetKey(_window->window(), GLFW_KEY_E);
    _keyQ = glfwGetKey(_window->window(), GLFW_KEY_A);
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
        else if (key == GLFW_KEY_SPACE || key == GLFW_KEY_P)
            pauseSimulation(!_pauseSimulation);
            // Displaying pause
        else if (key == GLFW_KEY_TAB)
            _pauseDisplaying = !_pauseDisplaying;
            // Get simulation time (in ants steps)
        else if (key == GLFW_KEY_ENTER) {
            double timeSimulation = glfwGetTime() - _beginSimulation;
            std::cout << _CYAN("Time of simulation :   ") << _count << " steps\n                       " << timeSimulation << " seconds\n"
                         _CYAN("Frequency of updates : ") <<_count / timeSimulation << "\n" <<
                         _YELLOW("--------------------------------------") << std::endl;
        }
            // Access to the previous rule
        else if (key == GLFW_KEY_KP_SUBTRACT || key == GLFW_KEY_PAGE_DOWN) {
            if (_currentPreConfiguredRules > 1)
                setRules(_currentPreConfiguredRules - 1);
            else
                setRules(PRE_CONFIGURED_RULES_NUMBER);
        }
            // Access to the next rule
        else if (key == GLFW_KEY_KP_ADD || key == GLFW_KEY_PAGE_UP) {
            if (_currentPreConfiguredRules < PRE_CONFIGURED_RULES_NUMBER)
                setRules(_currentPreConfiguredRules + 1);
            else
                setRules(1);
        }
            // User creates its own rules
        else if (key == GLFW_KEY_KP_ENTER) {
            createRules();
        } // display the current rules
        else if (key == GLFW_KEY_R) {
            std::cout << _BOLD(_BLUE("List of all the rules :\n")) << _rules->getRules() << std::endl;
        }
            // Get the composition of the grid TODO : display the number of each color cubes
        else if (key == GLFW_KEY_N) {
            std::cout << _BOLD(_BLUE("Composition of the grid : ")) << _grid->getSize() << _BOLD(_BLUE(" cubes.\n")) << std::endl;
        }
            // Reset the simulation
        else if (key == GLFW_KEY_BACKSPACE) {
            initialize();
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
    std::cout << _BOLD(_BLUE("\nCommands to control the 3D Langton's Ant simulation :\n"))
            _CYAN("[Arrows]    ")                       _YELLOW(": ") "Orientate the camera\n"
            _CYAN("[BACKSPACE] ")                       _YELLOW(": ") "Reset the simulation\n"
            _CYAN("[ENTER]     ")                       _YELLOW(": ") "Get the time of the simulation (on ant steps)\n"
            _CYAN("[ENTER-KP]  ")                       _YELLOW(": ") "Create our own rules\n"
            _CYAN("[Escape]    ")                       _YELLOW(": ") "Quit\n"
            _CYAN("[SCROLL]    ")                       _YELLOW(": ") "Zoom\n"
            _CYAN("[SPACE] ") _YELLOW("| ") _CYAN("P ") _YELLOW(": ") "Pause the simulation\n"
            _CYAN("[TAB]       ")                       _YELLOW(": ") "Pause the displaying\n"
            _CYAN("PageUp  ") _YELLOW("| ") _CYAN("+ ") _YELLOW(": ") "Load next pre-configured rule\n"
            _CYAN("PageDwn ") _YELLOW("| ") _CYAN("- ") _YELLOW(": ") "Load previous pre-configured rule\n"
            _CYAN("H           ")                       _YELLOW(": ") "Help message\n"
            _CYAN("N           ")                       _YELLOW(": ") "Get the number of cubes\n"
            _CYAN("R           ")                       _YELLOW(": ") "Display the current rules\n"
            _CYAN("X           ")                       _YELLOW(": ") "Eclate cubes" << std::endl;
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