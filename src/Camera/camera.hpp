#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../settings.hpp"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera();
    ~Camera();

    void updateSizes(int w, int h);
    void apply();
    void control(GLFWwindow* window);
private:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec2 mouse;
    Camera_settings cs;

    void loadSettings();
};

#endif // CAMERA_HPP
