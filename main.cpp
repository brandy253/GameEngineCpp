#include <bits/stdc++.h>
#include <stdlib.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "VersionDisplay.h"
#include "Loader.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using glm::mat4;
using glm::vec3;

using namespace std;

#define BUFFER_OFFSET(a) ((void*)(a))

GLuint VAOID;
GLuint VBOID[2];

Shader *shader;

mat4 rotationMatrix;
mat4 projectionMatrix;
mat4 translationMatrix;

float dx = 0.0f;
float dy = 0.0f;
float dz = 0.0f;

GLfloat angle = 0.0f;

GLfloat FOV = 70;
GLfloat NEAR_PLANE = 0.1f;
GLfloat FAR_PLANE = 1000.0f;

void init() {

    static const GLfloat vertices[6][3] = {
        {-1.0,-1.0, 0.0},{-1.0, 1.0, 0.0},{ 1.0,-1.0, 0.0},
        { 1.0,-1.0, 0.0},{-1.0, 1.0, 0.0},{ 1.0, 1.0, 0.0},
    };

    static const GLfloat colors[6][3] = {
        { 1.0, 0.0, 0.0},{ 0.0, 1.0, 0.0},{ 0.0, 0.0, 1.0},
        { 1.0, 1.0, 0.0},{ 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}
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

    //  Create projection matrix;
    float aspect_ratio = (float)1280 / (float)720;
    float y_scale = (1.0f / tan(glm::radians(FOV / 2.0f))) * aspect_ratio;
    float x_scale = y_scale / aspect_ratio;
    float frustum_length = FAR_PLANE - NEAR_PLANE;

    projectionMatrix = mat4(0.0f);
    projectionMatrix[0][0] = x_scale;
    projectionMatrix[1][1] = y_scale;
    projectionMatrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
    projectionMatrix[2][3] = -1;
    projectionMatrix[3][2] = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
    projectionMatrix[3][3] = 0.0f;

    //cout << projectionMatrix[0][0] << " " << projectionMatrix[0][1] << " " << projectionMatrix[0][2] << " " << projectionMatrix[0][3] << endl;
    //cout << projectionMatrix[1][0] << " " << projectionMatrix[1][1] << " " << projectionMatrix[1][2] << " " << projectionMatrix[1][3] << endl;
    //cout << projectionMatrix[2][0] << " " << projectionMatrix[2][1] << " " << projectionMatrix[2][2] << " " << projectionMatrix[2][3] << endl;
    //cout << projectionMatrix[3][0] << " " << projectionMatrix[3][1] << " " << projectionMatrix[3][2] << " " << projectionMatrix[3][3] << endl;
}

void display() {
    static const float black[] = { 0.7f, 0.7f, 0.7f, 0.0f };
    glClearBufferfv(GL_COLOR, 0, black);

    //  Do stuff with translation
    translationMatrix = glm::translate(mat4(1.0f), vec3(dx, dy, dz));
    GLuint translationMatrixLocation = glGetUniformLocation(shader->getProgramHandle(), "TranslationMatrix");
    if(translationMatrixLocation >= 0) {
        glUniformMatrix4fv(translationMatrixLocation, 1, GL_FALSE, &translationMatrix[0][0]);
    }

    //  Do stuff with rotation
    rotationMatrix = glm::rotate(mat4(1.0f), angle, vec3(0.0f, 1.0f, 0.0f));
    //angle = (angle + 0.001f);
    if(angle >= 360.0f) angle = 0.0f;

    GLuint location = glGetUniformLocation(shader->getProgramHandle(), "RotationMatrix");
    if(location >= 0) {
        glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);
    }

    //  Do stuff with projection / a.k.a camera view
    location = glGetUniformLocation(shader->getProgramHandle(), "ProjectionMatrix");
    if(location >= 0) {
        glUniformMatrix4fv(location, 1, GL_FALSE, &projectionMatrix[0][0]);
    }

    glBindVertexArray(VAOID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch(key) {
case GLFW_KEY_A:
    dx -= 0.01f;
    break;
case GLFW_KEY_D:
    dx += 0.01f;
    break;
case GLFW_KEY_W:
    dy += 0.01f;
    break;
case GLFW_KEY_S:
    dy -= 0.01f;
    break;
case GLFW_KEY_UP:
    cout << "UP" << endl;
    dz += 0.01f;
    break;
case GLFW_KEY_DOWN:
    cout << "DOWN" << endl;
    dz -= 0.01f;
    break;
default:
    break;
    }
}

int main()
{
    //  Init OpenGL
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Game Engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    gl3wInit();

    //  Display some information
    VersionDisplay *vd = new VersionDisplay(); vd->display();

    //  Init some data
    init();

    //  Init, load and build shaders
    Loader* loader = new Loader();
    GLchar* src = loader->LoadShaderSource("triangles.vert");

    shader = new Shader();
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
