#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <iostream>
#include <GL/gl.h>

unsigned int loadTexture(std::string file)
{
    //подготовка текстуры
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //загрузка текстуры
    float pixels[] = {
        0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //освобождение памяти
    glBindTexture(GL_TEXTURE_2D, 0);

    std::cout << textureID;
    return textureID;
}

#endif // TEXTURELOADER_H
