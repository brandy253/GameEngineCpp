#include "VersionDisplay.h"

VersionDisplay::VersionDisplay()
{
    //ctor
}

VersionDisplay::~VersionDisplay()
{
    //dtor
}

void VersionDisplay::display() {
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}
