#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct
{
    unsigned int id;
} Texture;

Texture load_texture(const char* path);

#endif