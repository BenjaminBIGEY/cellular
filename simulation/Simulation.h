//
// Created by benji on 08/11/16.
//

#ifndef LANGTON3D_SIMULATION_H
#define LANGTON3D_SIMULATION_H

#include <unistd.h>
#include <vector>
#include <sstream>

#include "Grid3D.h"
#include "Rendering/Context.h"
#include "Rendering/Scene.h"
#include "Rendering/Window.h"
#include "Elements/Ant.h"

#define DEFAULT_UPDATE_FREQUENCY 100 // Hz
#define LIMIT_SIMULATION 100 // divergence of the ant after

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
    /**
     * @param ruleID from 1 to PRE_CONFIGURED_RULES_NUMBER
     */
    Simulation(int ruleID = 0, float alpha = ALPHA_DEFAULT);
    Simulation(RuleDefinition rules, float alpha = ALPHA_DEFAULT);
    ~Simulation();

    void addAnt(int x, int y, int z, Orientation orientation = Orientation::FRONT);
    void addAnt(Vector3 position, Orientation orientation = Orientation::FRONT);


    void start();

    void initialize();

    void createRules();
    void setRules(int ruleID);
    void setRules(RuleDefinition rules);

    void setColor(int x, int y, int z, Color color);
    void setColor(Vector3 position, Color color);

    // change alpha component for each cube at the argument color
    void setAlpha(float alpha);

    void printHelp();

    // Initialize the 3D grid with initials cubes
    void debug();

protected:
    void mainLoop();

    void input();

    void createWindow();
    void createControlKeys();

    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) override;
    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) override;

private:
    std::unique_ptr<Scene> _scene = nullptr;

    std::unique_ptr<Window> _window = nullptr;
    std::shared_ptr<Grid3D> _grid = nullptr;
    std::shared_ptr<Rules> _rules = nullptr;

    std::vector<std::pair<Vector3, Orientation>> _antsPosition;
    std::vector<std::unique_ptr<Ant>> _listAnts;

    int _count = 0;
    int _currentPreConfiguredRules = 0;
    int _updateFrequency;
    double _time1Update;

    bool _pauseSimulation = false;
    bool _pauseDisplaying = false;
    bool _colored = true;
    bool _diverge = false;

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

    void emptyBuffer() {
        cin.clear();
        cin.seekg(0, ios::end);

        if (cin.eof())
            cin.ignore(numeric_limits<streamsize>::max());
        else
            cin.clear();
    }
};


#endif //LANGTON3D_SIMULATION_H
