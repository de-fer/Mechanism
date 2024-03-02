#ifndef MODEL_HPP
#define MODEL_HPP

#include <GLFW/glfw3.h>

class Model
{
public:
    Model();
    ~Model();
    void run();
private:
    void createWindow();

    GLFWwindow* window;
};

#endif // MODEL_HPP
