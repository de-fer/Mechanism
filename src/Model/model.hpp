#ifndef MODEL_HPP
#define MODEL_HPP

#include "../settings.hpp"
#include "../Object/object.hpp"
#include "../Camera/camera.hpp"

#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <map>

class Model
{
public:
    Model();
    ~Model();
    void run();

    void close();
    void swapMouse();
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
    std::map<std::string, unsigned int> textures;
    std::array<Object,3> objects;

    bool cursor_status = false;
};

#endif // MODEL_HPP
