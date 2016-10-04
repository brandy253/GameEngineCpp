#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Game Engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    gl3wInit();

    char *GL_version = (char *)glGetString(GL_VERSION);
    char *GL_vendor = (char *)glGetString(GL_VENDOR);
    char *GL_renderer = (char *)glGetString(GL_RENDERER);

    std::cout << "OpenGL version: " << GL_version << std::endl;
    std::cout << "OpenGL vendor: " << GL_vendor << std::endl;
    std::cout << "OpenGL renderer: " << GL_renderer << std::endl;
    return 0;
}
