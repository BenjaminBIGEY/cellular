//
// Created by benji on 08/11/16.
//

#ifndef LANGTON3D_SIMULATION_H
#define LANGTON3D_SIMULATION_H

#include <deque>

#include "Display/FileBuffer.h"
#include "Display/Display.h"
#include "Display/Rendering/Context.h"
#include "Display/Rendering/RenderableCube.h"
#include "Display/Rendering/Scene.h"
#include "Elements/Unit.h"
#include "Elements/Ant.h"


struct Cube {
    Cube(std::string name, std::shared_ptr<Unit> unit, std::shared_ptr<RenderableCube> render);
    std::shared_ptr<Unit> _unit = nullptr;
    std::shared_ptr<RenderableCube> _render = nullptr;
    FileBuffer _buffer;
};


class Simulation {
public:
    Simulation(int sizeX, int sizeY, int sizeZ, float sizeCube = 1.0f, Color colorInit = (Color)0);
    void addAnt(int x, int y, int z);
    ~Simulation();

    void mainLoop();

    bool continueMainLoop();

    void update(useconds_t usec); // microseconds


private:
    void render(std::shared_ptr<RenderableCube> object);

    void createControlKeys();

    std::unique_ptr<Display> _display = nullptr;
    std::shared_ptr<Scene> _scene = nullptr;
    Context* _context = nullptr;

    std::deque<std::deque<std::deque<Cube>>> _grid3D;
    std::vector<std::unique_ptr<Ant>> _listAnts;

    // Counter of moves
    int _count = 0;

    // Controls
    int _rightKey;
    int _leftKey;
    int _upKey;
    int _downKey;
};


#endif //LANGTON3D_SIMULATION_H
