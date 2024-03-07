#ifndef SCENE_HPP
#define SCENE_HPP

#include "../Object/object.hpp"

class Scene
{
public:
    Scene();
    ~Scene();

    std::string name;
    std::map<std::string, unsigned int> *textures;

    void setName(std::string name);
    void setTextures(std::map<std::string, unsigned int>* textures);

    void load();
    void draw();
private:
    std::vector<Object> objects;
};

#endif // SCENE_HPP
