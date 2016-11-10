//
// Created by benji on 08/11/16.
//

#include "Simulation.h"


Simulation::Simulation(int sizeX, int sizeY, int sizeZ, float sizeCube, Color colorInit) {
    _grid = std::make_shared<Grid3D>(sizeX, sizeY, sizeZ, sizeCube, colorInit);
    _scene = std::make_shared<Scene>(_grid);





    _display = make_unique<Display>();
    // Creating of context
    _context = new Context(_display->getWindow());
    // Initializing of the scene
    _scene = std::make_shared<Scene>();

    Light light(LIGHT_POINT, 0, 0, 0);
    _scene->setLight(light);

    _grid = make_unique<Grid3D>(sizeX, sizeY, sizeZ, sizeCube, colorInit);



    // Initialization of Graphic part
    _display = make_unique<Display>();
    if(!_display->initGL())
        exit(EXIT_FAILURE);


    createControlKeys();
}

Simulation::~Simulation() {


    _listAnts.clear();

    delete _context;
}

bool Simulation::continueMainLoop() {
    return _display->isWindowOpened();
}

void Simulation::mainLoop() {
    if (!_scene->getCamera().isTraveling()) {
        _scene->render(_context); // ?
        glm::vec3 cubeGraphicalPos;

        for(int x = 0 ; x < _grid3D.size() ; x++) {
            for(int y = 0 ; y < _grid3D[0].size() ; y ++) {
                for (int z = 0; z < _grid3D[0][0].size() ; z++) {
                    cubeGraphicalPos = _grid3D[x][y][z]._render->getPosition();
                    _scene->getCamera().moveCameraByCenterPoint(cubeGraphicalPos.x, cubeGraphicalPos.y, cubeGraphicalPos.z);

                    _grid3D[x][y][z]._render->render(_context); // ?
                }
            }
        }

        glm::vec3 cameraUp = _scene->getCamera().getUp();

        if (cameraUp.x == 0 && cameraUp.y == 0) {
            if (_rightKey == GLFW_PRESS && _leftKey != GLFW_PRESS) {
                _scene->getCamera().rotateZ(180.0f / 70.0f);
            }
            else if (_leftKey == GLFW_PRESS && _rightKey != GLFW_PRESS) {
                _scene->getCamera().rotateZ(- 180.0f / 70.0f);
            }

            if (_upKey == GLFW_PRESS && _downKey != GLFW_PRESS) {
                _scene->getCamera().rotateUpDown(180.0f / 70.0f);
            }
            else if (_downKey == GLFW_PRESS && _upKey != GLFW_PRESS) {
                _scene->getCamera().rotateUpDown(- 180.0f / 70.0f);
            }
        }

        for(auto ant : _listAnts) {
            Vector3 pos = ant->getPosition();
            ant->update(_grid3D[pos.x][pos.y][pos.z]._unit->getColor());
        }

        _scene->stopUseContext(_context); // ?
    }
}
/*
void Simulation::update(useconds_t usec) {
    _display->update();

    Vector3 antPosition(0,0,0);
    Color newColor;
    for(int i = 0 ; i < _listAnts.size() ; i++) {
        antPosition = _listAnts[i]->getPosition();
        newColor = _grid->getColor(antPosition);
        //_listAnts[i]->update(newColor);

        _grid->update(antPosition);
        auto pos = _listAnts[i].get()->getPosition();
        //std::cout << "The ant is at position : X = " << pos.x << " ; Y = " << pos.y << " ; Z = " << pos.z << ".\n";

        // TODO
        //display(antPosition, newColor);
    }


    usleep(usec);

    _count++;
}
*/
void Simulation::addAnt(int x, int y, int z) {
    std::unique_ptr<Ant> ant = make_unique<Ant>(x, y, z, Orientation::FRONT);
    _listAnts.push_back(std::move(ant));
}
/*
void Simulation::render(std::shared_ptr<RenderableCube> object) {
    _scene->render(_context);

    object->render(_context);

    _scene->stopUseContext(_context);
}*/

void Simulation::createControlKeys() {
    int rightKey = glfwGetKey(_display->getWindow(), GLFW_KEY_RIGHT);
    int leftKey = glfwGetKey(_display->getWindow(), GLFW_KEY_LEFT);
    int upKey = glfwGetKey(_display->getWindow(), GLFW_KEY_UP);
    int downKey = glfwGetKey(_display->getWindow(), GLFW_KEY_DOWN);
}

/*
 * Callbacks definition
 */
void Display::glfwErrorCallback(int error, const char* description) {
    std::cerr << "There was a glfw error : " << description << std::endl;
}

// Is called whenever a key is pressed/released via GLFW
void Display::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
/* EXAMPLES :
    if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS) {
        auto traveling = std::make_unique<Traveling>(
                scene->camera(), 0, 0, 30, 0, 0, 0, 0, 1, 0
        );
        traveling->setDuration(0.5f);
        scene->camera().traveling(traveling);
    }
    else if (key == GLFW_KEY_KP_1 && action == GLFW_PRESS) {
        auto traveling = std::make_unique<Traveling>(
                scene->camera(), 15, 15, 15, 0, 0, 0, 0, 0, 1
        );
        traveling->setDuration(0.5f);
        scene->camera().traveling(traveling);
    }*/
}

void Display::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    _scene->getCamera().zoom((float) pow(1.2, - yoffset));
}