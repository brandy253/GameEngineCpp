#ifndef LOADER_H
#define LOADER_H
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
class Loader
{
    public:
        Loader();
        virtual ~Loader();

        GLchar* LoadShaderSource(char* filename);
    protected:

    private:
};

#endif // LOADER_H
