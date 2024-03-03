#include "model.hpp"

#include <iostream>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

Model::Model()
{
    load_settings();

    //инициализация glfw
    try
    {
        glfwInit();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    this->createWindow();
}

Model::~Model()
{
    glfwTerminate();
}

void Model::run()
{
    while(!glfwWindowShouldClose(this->window))
    {
        glfwPollEvents(); //обработка ивентов окна
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        glfwSwapBuffers(this->window);
    }
}

void Model::load_settings()
{
    std::ifstream f("settings.json");
    if (f.is_open())
    {
        std::cout << "File is open!" << std::endl;
        try
        {
            json data = json::parse(f)["window"];
            std::cout << data << std::endl;

            //записываем считанные параметры
            this->ws.fullscreen = data["fullscreen"];
            this->ws.width = data["width"];
            this->ws.height = data["height"];
            this->ws.bg_r = data["bg_color"]["r"];
            this->ws.bg_g = data["bg_color"]["g"];
            this->ws.bg_b = data["bg_color"]["b"];
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        std::cout << "File is close!" << std::endl;
        f.close();
    }
    else
    {
        std::cerr << "File isnt open!" << std::endl;
        exit(1);
    }
}

void Model::createWindow()
{
    if (this->ws.fullscreen)
        this->window = glfwCreateWindow(
            this->ws.width, this->ws.height,
            "Mechanism", glfwGetPrimaryMonitor(), nullptr);
    else
        this->window = glfwCreateWindow(
            this->ws.width, this->ws.height,
            "Mechanism", nullptr, nullptr);
    glfwMakeContextCurrent(this->window);
    glClearColor(this->ws.bg_r, this->ws.bg_g, this->ws.bg_b, 1.f); //заливка заднего фона
}
