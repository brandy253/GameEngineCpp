#ifndef SHADER_H
#define SHADER_H
#include <stdlib.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
using namespace std;

class Shader
{
    public:
        Shader();
        virtual ~Shader();
        void createVertexShader();
        void compileVertexShader(char *src);

        void createFragmentShader();
        void compileFragmentShader(char *src);

        void build();

    protected:

    private:
        int vertexShader;
        int fragmentShader;
};

#endif // SHADER_H
