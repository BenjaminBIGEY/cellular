//
// Created by benji on 08/11/16.
//

#ifndef LANGTON3D_SIMULATION_H
#define LANGTON3D_SIMULATION_H

#include <unistd.h>
#include <vector>

#include "Grid3D.h"
#include "Rendering/Context.h"
#include "Rendering/Scene.h"
#include "Rendering/Window.h"
#include "Elements/Ant.h"

class EventListener {
public:
    void init(Window * mainWindow);

    virtual void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) = 0;
    virtual void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) = 0;

    void setEventListener(EventListener* eventListener);

    static EventListener *listener;
protected:
    void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};


const float ALPHA_DEFAULT = 0.8f;

class Simulation : public EventListener {

public:
    Simulation(Color colorInit = (Color)0, float alpha = ALPHA_DEFAULT);
    ~Simulation();
    void addAnt(int x, int y, int z, Orientation orientation = Orientation::FRONT);
    void addAnt(Vector3 position, Orientation orientation = Orientation::FRONT);

    void start(int updatePerSecond = 100);

    void setColor(int x, int y, int z, Color color);
    void setColor(Vector3 position, Color color);

    // change alpha component for each cube at the argument color
    void setAlpha(Color color);

private:
    void mainLoop();

    void input();

    void createWindow();
    void createControlKeys();

    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) override;
    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) override;

    std::unique_ptr<Scene> _scene = nullptr;

    std::unique_ptr<Window> _window = nullptr;
    std::shared_ptr<Grid3D> _grid = nullptr;
    std::vector<std::unique_ptr<Ant>> _listAnts;


    int _count = 0;
    int _updatePerSecond;
    double _time1Update;

    bool _pause = false;

    // Controls
    int _rightKey;
    int _leftKey;
    int _upKey;
    int _downKey;

    int _keyA; // +Y
    int _keyZ; // +Z
    int _keyE; // -Y
    int _keyQ; // -X
    int _keyS; // -Z
    int _keyD; // +X
};


#endif //LANGTON3D_SIMULATION_H
