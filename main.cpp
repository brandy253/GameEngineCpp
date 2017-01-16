#include <bits/stdc++.h>
#include <stdlib.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "VersionDisplay.h"
#include "Loader.h"
#include "Shader.h"

using namespace std;

#define BUFFER_OFFSET(a) ((void*)(a))

GLuint VAOID;
GLuint VBOID[2];

void init() {

    static const GLfloat vertices[6][3] = {
        {-0.9,-0.9, 0.0},{-0.9, 0.9, 0.0},{ 0.9,-0.9, 0.0},
        { 0.9,-0.9, 0.0},{-0.9, 0.9, 0.0},{ 0.9, 0.9, 0.0},
    };

    static const GLfloat colors[6][3] = {
        { 1.0, 0.0, 0.0},{ 1.0, 0.0, 0.0},{ 1.0, 0.0, 0.0},
        { 1.0, 0.0, 0.0},{ 1.0, 0.0, 0.0},{ 1.0, 0.0, 0.0}
    };

    //  create 2 VBOs for position and color
    glGenBuffers(2, VBOID);

    //  populate the for position buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBOID[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(float), vertices, GL_STATIC_DRAW);

    //  populate the color buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBOID[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(float), colors, GL_STATIC_DRAW);

    //  create the vao
    glGenVertexArrays(1, &VAOID);
    glBindVertexArray(VAOID);

    //  enable the vertex attribute arrays
    glEnableVertexAttribArray(0);   // vertex position
    glEnableVertexAttribArray(1);   // vertex color

    //  map index 0 to the position buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBOID[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    //  map index 1 to the color buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBOID[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glDisable(GL_PROGRAM_POINT_SIZE);
    glPointSize(10.0);
}

void display() {
    static const float black[] = { 0.7f, 0.7f, 0.7f, 0.0f };
    glClearBufferfv(GL_COLOR, 0, black);
    glBindVertexArray(VAOID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main()
{
    //  Init OpenGL
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Game Engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    gl3wInit();

    //  Display some information
    VersionDisplay *vd = new VersionDisplay(); vd->display();

    //  Init some data
    init();

    //  Init, load and build shaders
    Loader* loader = new Loader();
    GLchar* src = loader->LoadShaderSource("triangles.vert");

    Shader *shader = new Shader();
    shader->createVertexShader();
    shader->compileVertexShader(src);

    src = loader->LoadShaderSource("triangles.frag");
    shader->createFragmentShader();
    shader->compileFragmentShader(src);

    shader->build();

    //  Main loop
    while(!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
