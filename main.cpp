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

<<<<<<< HEAD
=======
#define BUFFER_OFFSET(a) ((void*)(a))

GLuint VAOID;
GLuint VBOID;

void init() {

    static const GLfloat vertices[6][2] = {
        {-0.90,-0.90},{ 0.85,-0.90},{-0.90, 0.85},
        { 0.90,-0.85},{ 0.90, 0.90},{-0.85, 0.90}
    };
    glGenVertexArrays(1, &VAOID);
    glBindVertexArray(VAOID);

    glGenBuffers(1, &VBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
}

void display() {
    static const float black[] = { 0.5f, 0.5f, 0.5f, 0.0f };
    glClearBufferfv(GL_COLOR, 0, black);
    glBindVertexArray(VAOID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main()
{
>>>>>>> origin/master
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Game Engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    gl3wInit();

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
<<<<<<< HEAD
=======
    std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
>>>>>>> origin/master

    init();

    while(!glfwWindowShouldClose(window)) {
<<<<<<< HEAD

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
=======
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

>>>>>>> origin/master
    return 0;
}
