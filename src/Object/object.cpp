#include "object.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/gl.h>

Object::Object()
{
    this->pos = glm::vec3();
    this->orient = glm::vec3();
}

Object::~Object()
{

}

void Object::draw()
{
    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, this->pos.z);
    glRotatef(this->orient.z, 0.f, 0.f, 1.f);
    glRotatef(this->orient.x, 1.f, 0.f, 0.f);
    glRotatef(this->orient.y, 0.f, 1.f, 0.f);

    glColor3f(1.f,1.f,1.f);
    glVertexPointer(3, GL_FLOAT, 0, this->vertexes.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    if (this->textured)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        glTexCoordPointer(2, GL_FLOAT, 0, this->uv.data());
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    else
    {
        glColorPointer(3, GL_FLOAT, 0, this->colors.data());
        glEnableClientState(GL_COLOR_ARRAY);
    }

    if (this->draw_faces)
    {
        glDrawElements(GL_TRIANGLES, this->faces.size()*3, GL_UNSIGNED_INT, this->faces.data());
    }
    if (this->draw_frame)
    {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        //glDisableClientState(GL_COLOR_ARRAY);
        glDrawElements(GL_LINES, this->edges.size()*2, GL_UNSIGNED_INT, this->edges.data());
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    if (this->textured){
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }


    glPopMatrix();
}

extern std::string DATA_PATH;
void Object::loadFromFile(const char* fileName)
{
    std::ifstream f(DATA_PATH + "\\objects\\" + fileName);
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
            //комментарий
            if (fw == "textured") {
                this->textured = true;
                continue;
            }
            if (fw == "draw_frame") {
                this->draw_frame = true;
                continue;
            }
            if (fw == "draw_faces") {
                this->draw_faces = true;
                continue;
            }

            //вершина
            if (fw == "v") {
                float x, y, z = 0;
                str >> x; str >> y; str >> z;
                this->vertexes.push_back({x, y, z});
                continue;
            }
            //цвет
            if (fw == "c") {
                if (this->textured) continue;
                float r, g, b;
                str >> r; str >> g; str >> b;
                this->colors.push_back({r, g, b});
                continue;
            }
            //uv координаты
            if (fw == "uv") {
                if (!this->textured) continue;
                float u, v;
                str >> u; str >> v;
                this->uv.push_back({u, v});
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

void Object::setTexture(unsigned int texture)
{
    this->texture = texture;
}

void Object::drawFrame(bool val)
{
    this->draw_frame = val;
}
void Object::drawFaces(bool val)
{
    this->draw_faces = val;
}

void Object::setPosition(float x, float y, float z)
{
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
}
void Object::setOrientation(float x, float y, float z)
{
    this->orient.x = x;
    this->orient.y = y;
    this->orient.z = z;
}
