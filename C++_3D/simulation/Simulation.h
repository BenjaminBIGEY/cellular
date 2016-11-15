//
// Created by benji on 08/11/16.
//

#ifndef LANGTON3D_SIMULATION_H
#define LANGTON3D_SIMULATION_H

#include <unistd.h>

#include "Grid3D.h"
#include "Rendering/Context.h"
#include "Rendering/Scene.h"
#include "Rendering/Window.h"
#include "Elements/Ant.h"

class EventListener;
static std::vector<std::shared_ptr<EventListener>> _listListeners;

class EventListener {
public:
    static void init(Window * window);

    virtual void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) = 0;
    virtual void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) = 0;
/*
    static int getSizeListeners() {return (int)_listListeners.size();}
    static std::vector<std::shared_ptr<EventListener>> getListListener() {return _listListeners;}
*/
private:
    static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};


class Simulation : public EventListener {
public:
    Simulation(int sizeX, int sizeY, int sizeZ, Color colorInit = (Color)0);
    ~Simulation();
    void addAnt(int x, int y, int z);

    void start(int fps = 60);

    void setColor(int x, int y, int z, Color color);

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

    // Controls
    int _rightKey;
    int _leftKey;
    int _upKey;
    int _downKey;
    int _plusKey;
    int _minusKey;
};


#endif //LANGTON3D_SIMULATION_H
