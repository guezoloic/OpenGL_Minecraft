#ifndef EBO_HPP
#define EBO_HPP

#include <GL/glew.h>

class EBO
{
private:
    GLuint id;

public:
    EBO(unsigned int* indices, size_t size);
    ~EBO();

    void bind();
    void unbind();
};
#endif