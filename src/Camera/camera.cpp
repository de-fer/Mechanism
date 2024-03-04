#include "camera.hpp"

#include <iostream>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Camera::Camera()
{
    this->pos = glm::vec3();
    this->rot = glm::vec3();
    this->mouse = glm::vec2();
    this->loadSettings();

    //this->updateSizes(1,1);
}

Camera::~Camera()
{

}

void Camera::updateSizes(int w, int h)
{
    float k = w/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-this->cs.size*k,this->cs.size*k, -this->cs.size, this->cs.size, this->cs.size*this->cs.near,this->cs.size*this->cs.far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-90,1.f,0.f,0.f);
}

void Camera::apply()
{
    glRotatef(-this->rot.z,0.f,1.f,0.f);
    glRotatef(-this->rot.y,1.f,0.f,0.f);
    glRotatef(-this->rot.x,0.f,0.f,1.f);
    glTranslatef(-this->pos.x, -this->pos.y, -this->pos.z);
}

//в будущем переделеать всё через интерфейсы
void Camera::control(GLFWwindow *window)
{
    //скорость камеры
    float speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) speed = this->cs.speed * this->cs.speed_multiple;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) speed = this->cs.speed;

    //движение мышью
    double mnx, mny;
    glfwGetCursorPos(window, &mnx, &mny);
    this->rot += glm::vec3((this->mouse.x-mnx)*this->cs.mouse_multiple,(this->mouse.y-mny)*this->cs.mouse_multiple,0.f);
    this->mouse.x = mnx;
    this->mouse.y = mny;

    //кнопки на клавиатуре
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) rot += glm::vec3(0.f,1.f,0.f);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) rot += glm::vec3(0.f,-1.f,0.f);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rot += glm::vec3(-1.f,0.f,0.f);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rot += glm::vec3(1.f,0.f,0.f);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pos += glm::vec3(-std::sin(glm::radians(rot.x))*speed,std::cos(glm::radians(rot.x))*speed,0.f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pos += glm::vec3(std::sin(glm::radians(rot.x))*speed,-std::cos(glm::radians(rot.x))*speed,0.f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) pos += glm::vec3(std::cos(glm::radians(rot.x))*speed,std::sin(glm::radians(rot.x))*speed,0.f);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) pos += glm::vec3(-std::cos(glm::radians(rot.x))*speed,-std::sin(glm::radians(rot.x))*speed,0.f);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) pos += glm::vec3(0.f,0.f,speed);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) pos += glm::vec3(0.f,0.f,-speed);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) pos += glm::vec3(0.f,0.f,-speed);
}

void Camera::loadSettings()
{
    std::ifstream f("settings.json");
    if (f.is_open())
    {
        std::cout << "camera:File is open!" << std::endl;
        try
        {
            json data = json::parse(f)["camera"];
            //std::cout << data << std::endl;

            //записываем считанные параметры
            this->cs.size = data["size"];
            this->cs.speed = data["speed"];
            this->cs.speed_multiple = data["speed_multiple"];
            this->cs.near = data["near"];
            this->cs.far = data["far"];
            this->cs.mouse_multiple = data["mouse_multiple"];
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        std::cout << "camera:File is close!" << std::endl;
        f.close();
    }
    else
    {
        std::cerr << "camera:File isnt open!" << std::endl;
        exit(1);
    }
}
