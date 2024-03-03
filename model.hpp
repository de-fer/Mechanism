#ifndef MODEL_HPP
#define MODEL_HPP

#include "settings.hpp"

#include <GLFW/glfw3.h>

class Model
{
public:
    Model();
    ~Model();
    void run();
private:
    void load_settings();
    Window_settings ws;
    void applyHints();
    void createWindow();
    GLFWwindow* window;
};

#endif // MODEL_HPP
