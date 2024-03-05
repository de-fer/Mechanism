#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <array>
#include <vector>

class Object
{
public:
    Object();
    ~Object();

    bool draw_frame = false,
    draw_faces = false;

    void draw();

    void loadFromFile(const char* fileName);
    void setTexture(unsigned int texture);
private:
    unsigned int texture = 0;

    bool textured = false;
    std::vector<std::array<float, 3>> vertexes;
    std::vector<std::array<float, 3>> colors;
    std::vector<std::array<float, 2>> uv;
    std::vector<std::array<unsigned int, 2>> edges;
    std::vector<std::array<unsigned int, 3>> faces;
};

#endif // OBJECT_HPP
