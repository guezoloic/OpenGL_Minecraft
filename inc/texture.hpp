#ifndef TEXTUTE_HPP
#define TEXTUTE_HPP

#include "glad/glad.h"
#include <string>

class Texture
{
private:
    unsigned int id;

public:
    Texture(const std::string& path);
    ~Texture();

    void bind(GLenum textureUnit) const;
    unsigned int getID() const;
};

#endif