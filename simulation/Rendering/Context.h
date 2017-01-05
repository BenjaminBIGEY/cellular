//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_CONTEXT_H
#define LANGTON3D_CONTEXT_H


#include <GLFW/glfw3.h>
#include <memory>
#include <map>

#include "Program.h"

class Material;
class Program;

class Context {

public :
    Context(GLFWwindow *window);
    void setWindow(GLFWwindow * window);
    void getWindowDimensions(int &width, int &height);

    void pushMaterial(Material &material);

    void loadProgram(std::string name, std::string vertexShader, std::string fragmentShader);
    void setCurrentProgram(std::string currentProgramID);
    Program& program() {return *_programMap.at(this->_currentProgram);}
private :
    GLFWwindow *_window;

    std::string _currentProgram;
    std::map<std::string, std::shared_ptr<Program>> _programMap;
};


#endif //LANGTON3D_CONTEXT_H
