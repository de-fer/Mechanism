#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <array>
#include <vector>
#include <glm/vec3.hpp>

class Object
{
public:
    Object();
    ~Object();

    void draw();

    void loadFromFile(const char* fileName);
    void setTexture(unsigned int texture);

    void drawFrame(bool val);
    void drawFaces(bool val);

    glm::vec3 pos;
    glm::vec3 orient;

    void setPosition(float x, float y, float z);
    void setOrientation(float x, float y, float z);
private:
    unsigned int texture = 0;

    bool textured = false,
        draw_frame = false,
        draw_faces = false;
    std::vector<std::array<float, 3>> vertexes;
    std::vector<std::array<float, 3>> colors;
    std::vector<std::array<float, 2>> uv;
    std::vector<std::array<unsigned int, 2>> edges;
    std::vector<std::array<unsigned int, 3>> faces;
};

#endif // OBJECT_HPP
