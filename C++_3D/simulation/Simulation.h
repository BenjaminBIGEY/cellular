//
// Created by benji on 08/11/16.
//

#ifndef LANGTON3D_SIMULATION_H
#define LANGTON3D_SIMULATION_H

#include <unistd.h>

#include "Grid3D.h"
#include "Display/Rendering/Context.h"
#include "Display/Rendering/Scene.h"
#include "Display/Rendering/Window.h"
#include "Elements/Ant.h"


class Simulation {
public:
    Simulation(int sizeX, int sizeY, int sizeZ, float sizeCube = 1.0f, Color colorInit = (Color)0);
    ~Simulation();
    void addAnt(int x, int y, int z);

    void mainLoop(useconds_t usec);

    bool continueSimulation();


private:
    void updateSimulation();
    void input();

    void createControlKeys();
    static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    std::shared_ptr<Scene> _scene = nullptr;

    std::unique_ptr<Window> _window = nullptr;
    std::shared_ptr<Grid3D> _grid = nullptr;
    std::vector<std::unique_ptr<Ant>> _listAnts;

    int _count = 0;

    // Controls
    int _rightKey;
    int _leftKey;
    int _upKey;
    int _downKey;
};


#endif //LANGTON3D_SIMULATION_H
