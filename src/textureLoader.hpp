#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <iostream>
#include <GL/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void generateDefaultTexture()
{
    //подготовка текстуры
    glBindTexture(GL_TEXTURE_2D, 0);

    //создание изображения
    float pixels[] = {
        0, 0, 0,   1, 0, 1,
        1, 0, 1,   0, 0, 0,
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

    //настройка текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

unsigned int loadTexture(std::string file)
{
    //подготовка текстуры
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //загрузка текстуры
    int w, h, count;
    unsigned char *data = stbi_load(file.data(), &w, &h, &count, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, count == 4? GL_RGBA : GL_RGB, w, h, 0, count == 4? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

    //настройка текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //освобождение памяти
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

#endif // TEXTURELOADER_H
