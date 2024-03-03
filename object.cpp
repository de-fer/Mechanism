#include "object.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/gl.h>

Object::Object()
{

}

Object::~Object()
{

}

void Object::draw()
{
    glVertexPointer(3, GL_FLOAT, 0, this->vertexes.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, this->colors.data());
    glEnableClientState(GL_COLOR_ARRAY);

    if (this->draw_faces)
    {
        //glEnableClientState(GL_COLOR_ARRAY); //тк уже включено
        glDrawElements(GL_TRIANGLES, this->faces.size()*3, GL_UNSIGNED_INT, this->faces.data());
    }
    if (this->draw_frame)
    {
        glDisableClientState(GL_COLOR_ARRAY);
        glColor3f(0.f,1.f,1.f);
        glDrawElements(GL_LINES, this->edges.size()*2, GL_UNSIGNED_INT, this->edges.data());
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Object::loadFromFile(const char* fileName)
{
    std::ifstream f(fileName);
    if (f.is_open())
    {
        std::string line;
        while (std::getline(f, line))
        {
            std::string fw;
            std::stringstream str(line);
            str >> fw;
            //комментарий
            if (fw == "#") continue;

            //вершина
            if (fw == "v") {
                float x, y, z = 0;
                str >> x; str >> y; str >> z;
                this->vertexes.push_back({x, y, z});
                continue;
            }
            //цвет
            if (fw == "c") {
                float r, g, b;
                str >> r; str >> g; str >> b;
                this->colors.push_back({r, g, b});
                continue;
            }
            //грань
            if (fw == "e") {
                unsigned int v1, v2;
                str >> v1; str >> v2;
                this->edges.push_back({v1, v2});
                continue;
            }
            //поверхность
            if (fw == "f") {
                unsigned int v1, v2, v3;
                str >> v1; str >> v2; str >> v3;
                this->faces.push_back({v1, v2, v3});
                continue;
            }
        }
    }
    else
    {
        std::cerr << "File didnt open! Object didnt load!" << std::endl;
    }
}
