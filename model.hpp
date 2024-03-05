#ifndef MODEL_HPP
#define MODEL_HPP

#include "settings.hpp"
#include "object.hpp"
#include "src/Camera/camera.hpp"

#include <GLFW/glfw3.h>
#include <vector>

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
    Camera camera;
    void scene();
    void loadTextures();
    std::vector<unsigned int> textures;
    std::array<Object,3> objects;
};

#endif // MODEL_HPP
