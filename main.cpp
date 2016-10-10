#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
using namespace std;

GLuint VAOId;

void init() {
    static const GLfloat vertices[6][2] = {
        {-0.90,-0.90},{0.85,-0.90},{-0.90, 0.85},
        { 0.90,-0.85},{0.90, 0.90},{-0.85, 0.90}
    };

    glGenVertexArrays(1, &VAOId);
    glBindVertexArray(VAOId);
}

void display() {

}

int main() {

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Game Engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    gl3wInit();

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    init();

    while(!glfwWindowShouldClose(window)) {

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
