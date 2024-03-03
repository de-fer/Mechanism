#include "model.hpp"

#include <iostream>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

Model::Model()
{
    this->load_settings();

    //инициализация glfw
    try
    {
        glfwInit();
        this->createWindow();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
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
            //std::cout << data << std::endl;

            //записываем считанные параметры
            this->ws.fullscreen = data["fullscreen"];
            this->ws.width = data["width"];
            this->ws.height = data["height"];
            this->ws.bg_r = data["bg_color"]["r"];
            this->ws.bg_g = data["bg_color"]["g"];
            this->ws.bg_b = data["bg_color"]["b"];
            this->ws.bg_a = data["bg_color"]["a"];

            this->ws.RESIZABLE = data["RESIZABLE"];
            this->ws.DECORATED = data["DECORATED"];
            this->ws.FOCUSED = data["FOCUSED"];
            this->ws.FLOATING = data["FLOATING"];
            this->ws.MAXIMIZED = data["MAXIMIZED"];
            this->ws.CENTER_CURSOR = data["CENTER_CURSOR"];
            this->ws.TRANSPARENT_FRAMEBUFFER = data["TRANSPARENT_FRAMEBUFFER"];
            this->ws.MOUSE_PASSTHROUGH = data["MOUSE_PASSTHROUGH"];
            int temp = data["POSITION_X"];
            if (temp > -9999) this->ws.POSITION_X = temp;
            else this->ws.POSITION_X = GLFW_ANY_POSITION;
            temp = data["POSITION_Y"];
            if (temp > -9999) this->ws.POSITION_Y = temp;
            else this->ws.POSITION_Y = GLFW_ANY_POSITION;
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

void Model::applyHints()
{
    glfwWindowHint(GLFW_RESIZABLE, this->ws.RESIZABLE);
    glfwWindowHint(GLFW_DECORATED, this->ws.DECORATED);
    glfwWindowHint(GLFW_FOCUSED, this->ws.FOCUSED);
    glfwWindowHint(GLFW_FLOATING, this->ws.FLOATING);
    glfwWindowHint(GLFW_MAXIMIZED, this->ws.MAXIMIZED);
    glfwWindowHint(GLFW_CENTER_CURSOR, this->ws.CENTER_CURSOR);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, this->ws.TRANSPARENT_FRAMEBUFFER);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, this->ws.MOUSE_PASSTHROUGH);
    glfwWindowHint(GLFW_POSITION_X, this->ws.POSITION_X);
    glfwWindowHint(GLFW_POSITION_Y, this->ws.POSITION_Y);
}

void Model::createWindow()
{
    this->applyHints();
    if (this->ws.fullscreen)
        this->window = glfwCreateWindow(
            this->ws.width, this->ws.height,
            "Mechanism", glfwGetPrimaryMonitor(), nullptr);
    else
        this->window = glfwCreateWindow(
            this->ws.width, this->ws.height,
            "Mechanism", nullptr, nullptr);
    glfwMakeContextCurrent(this->window);
    glClearColor(this->ws.bg_r, this->ws.bg_g, this->ws.bg_b, this->ws.bg_a); //заливка заднего фона
}
