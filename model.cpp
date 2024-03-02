#include "model.hpp"

#include <iostream>
#include <exception>
#include <stdexcept>

Model::Model()
{
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
    std::cout << "Model's mainloop runned" << std::endl;
    while(!glfwWindowShouldClose(this->window))
    {
        glfwPollEvents(); //обработка ивентов окна
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        glfwSwapBuffers(this->window);
    }
}

void Model::createWindow()
{
    this->window = glfwCreateWindow(400, 400, "Mechanism", nullptr, nullptr);
    glfwMakeContextCurrent(this->window);
    glClearColor(0.7f, 0.7f, 0.7f, 1.f); //заливка заднего фона
}
