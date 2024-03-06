#include "model.hpp"

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

extern Model model;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        model.close();
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
        model.swapMouse();
}


Model::Model()
{
    this->loadSettings();
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
    //загрузка текстур
    this->loadTextures();

    glfwSetKeyCallback(this->window, key_callback);

    //переместить в loadScene()
    this->objects.at(0).loadFromFile("axis.txt");
    this->objects.at(1).loadFromFile("square.txt");
    this->objects.at(2).loadFromFile("triangle.txt");
    this->objects.at(1).setTexture(this->textures.at(0));

    this->objects.at(1).setPosition(0,2,0);
    this->objects.at(2).setPosition(2,0,0);
    this->objects.at(1).setOrientation(0,0,-45);
    this->objects.at(2).setOrientation(0,0,-45);
}

Model::~Model()
{
    glfwTerminate();
}

void Model::run()
{
    while(!glfwWindowShouldClose(this->window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (this->cursor_status) this->camera.control(this->window);
        this->display();
        glFlush();
        glfwSwapBuffers(this->window);
        glfwPollEvents(); //обработка ивентов окна
    }
}

extern std::string DATA_PATH; //путь к папке data
void Model::loadSettings()
{
    std::ifstream f("settings.json");
    if (f.is_open())
    {
        std::cout << "model:File is open!" << std::endl;
        try
        {
            json data = json::parse(f);
            DATA_PATH = data["data_path"]; //сохраняем путь к папке data
            data = data["window"];//переходим в настройки window
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
        std::cout << "model:File is close!" << std::endl;
        f.close();
    }
    else
    {
        std::cerr << "model:File isnt open!" << std::endl;
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

    this->swapMouse(); //выключаем курсор

    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_NORMALIZE);

    glLineWidth(2);

    glClearColor(this->ws.bg_r, this->ws.bg_g, this->ws.bg_b, this->ws.bg_a); //заливка заднего фона
}

void Model::display()
{
    glfwGetWindowSize(this->window, &this->ws.width, &this->ws.height);

    //главный вид
    glPushMatrix();
    if (this->ws.width > this->ws.height) {
        glViewport(0, (this->ws.height - this->ws.width) / 2, this->ws.width, this->ws.width);
    } else {
        glViewport((this->ws.width - this->ws.height) / 2, 0, this->ws.height, this->ws.height);
    }
    this->camera.updateSizes(this->ws.width, this->ws.height);
    this->camera.apply();
    this->scene();
    glPopMatrix();
}

void Model::scene()
{
    for (int i =0; i < this->objects.size(); ++i)
        this->objects.at(i).draw();
}

#include "../textureLoader.hpp"
void Model::loadTextures()
{
    generateDefaultTexture();
    this->textures.push_back(loadTexture(DATA_PATH+"\\textures\\"+"t1.png"));
}

void Model::close()
{
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void Model::swapMouse()
{
    if (!this->cursor_status)
        glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    this->cursor_status = !this->cursor_status;
    /* GLFW_CURSOR_NORMAL - обычный режим
     * GLFW_CURSOR_DISABLED - курсор выключен
     * GLFW_CURSOR_HIDDEN - курсор невидим
     */
}
