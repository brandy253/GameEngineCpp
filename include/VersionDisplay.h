#ifndef VERSIONDISPLAY_H
#define VERSIONDISPLAY_H
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>

class VersionDisplay
{
    public:
        VersionDisplay();
        virtual ~VersionDisplay();

        void display();
    protected:

    private:
};

#endif // VERSIONDISPLAY_H
