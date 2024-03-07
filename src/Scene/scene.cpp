#include "scene.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <glm/vec3.hpp>

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::setName(std::string name)
{
    this->name = name;
}
void Scene::setTextures(std::map<std::string, unsigned int> *textures)
{
    this->textures = textures;
}

void Scene::draw()
{
    for (int i =0; i < this->objects.size(); ++i)
        this->objects.at(i).draw();
}

extern std::string DATA_PATH; //путь к папке data
void Scene::load()
{
    //тут можно изменить формат файла сцены
    std::ifstream f(DATA_PATH + "\\scenes\\" + this->name + ".txt");
    if (f.is_open())
    {
        std::string line;
        while (std::getline(f, line))
        {
            std::string fw;
            std::stringstream str(line);
            str >> fw;
            if (fw == "#") continue;

            if (fw == "o")
            {
                Object obj;
                std::string obj_name;
                str >> obj_name;
                std::cout << "obj_name:" << obj_name << std::endl;
                obj.loadFromFile(obj_name.c_str());
                float x, y, z;
                str >> x >> y >> z;
                obj.setPosition(x, y, z);
                str >> x >> y >> z;
                obj.setOrientation(x, y, z);
                obj.setTexture(this->textures);
                this->objects.push_back(obj);
                continue;
            }

            if (fw == "t")
            {
                std::string texture_name;
                str >> texture_name;
                this->objects.back().changeTextureName(texture_name);
                this->objects.back().setTexture(this->textures);
            }
        }
    }
    else
    {
        std::cerr << "ERR::SCENE::File didnt open! Scene didnt load!" << std::endl;
        return;
    }
    std::cout << "SCENE::Scene loaded! Objects count: " << this->objects.size() << std::endl;
}
