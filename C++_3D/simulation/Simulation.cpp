//
// Created by benji on 08/11/16.
//

#include "Simulation.h"

Cube::Cube(std::string name, std::shared_ptr<Unit> unit, std::shared_ptr<RenderableCube> render) : _buffer(name) {
    _unit = unit;
    _render = render;
}

Simulation::Simulation(int sizeX, int sizeY, int sizeZ, float sizeCube, Color colorInit) {
    _display = make_unique<Display>();
    // Creating of context
    _context = new Context(_display->getWindow());
    // Initializing of the scene
    _scene = std::make_shared<Scene>();

    Light light(LIGHT_POINT, 0, 0, 0);
    _scene->setLight(light);


    _grid3D.clear();

    for(int x = 0 ; x < sizeX ; x++) {
        std::deque<std::deque<Cube> > grid2D;

        for(int y = 0 ; y < sizeY ; y ++) {
            std::deque<Cube> v;

            for (int z = 0; z < sizeZ; z++) {
                // Add cube
                std::shared_ptr<Unit> unit = std::make_shared<Unit>(colorInit);
                std::shared_ptr<RenderableCube> cubeRender = std::make_shared<RenderableCube>(sizeCube);
                cubeRender->getMaterial().setDiffuse(1.0f, 1.0f, 1.0f);
                //cubeRender->addTexturePath("assets/cubeInit.png");

                v.emplace_back(Cube(std::to_string(x) + ',' + std::to_string(y) + ',' + std::to_string(z),
                                    unit,
                                    cubeRender));

                //_display->addObjectScene(v[z]._render);
            }
            grid2D.push_back(std::move(v));
        }
        _grid3D.push_back(std::move(grid2D));
    }


    // Initialization of Graphic part
    _display = make_unique<Display>();
    if(!_display->initGL())
        exit(EXIT_FAILURE);


    createControlKeys();
}

Simulation::~Simulation() {
    _grid3D[0][0].clear();
    _grid3D[0].clear();
    _grid3D.clear();

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

void Simulation::render(std::shared_ptr<RenderableCube> object) {
    _scene->render(_context);

    object->render(_context);

    _scene->stopUseContext(_context);
}

void Simulation::createControlKeys() {
    int rightKey = glfwGetKey(_display->getWindow(), GLFW_KEY_RIGHT);
    int leftKey = glfwGetKey(_display->getWindow(), GLFW_KEY_LEFT);
    int upKey = glfwGetKey(_display->getWindow(), GLFW_KEY_UP);
    int downKey = glfwGetKey(_display->getWindow(), GLFW_KEY_DOWN);
}