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
    void loadSettings();
    Window_settings ws;
    void applyHints();

    void createWindow();
    GLFWwindow* window;

    void display();
};

#endif // MODEL_HPP
