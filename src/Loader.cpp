#include "Loader.h"

Loader::Loader()
{
    //ctor
}

Loader::~Loader()
{
    //dtor
}

GLchar* Loader::LoadShaderSource(char* filename) {
    //  Load vertex shader code
    cout << endl << "Opening shader source file " << filename << "...";
    FILE *p = fopen(filename, "rb");
    if(p == NULL) { cout << endl << "Error while opening " << filename << endl; return 0; }
    fseek(p, 0, SEEK_END);
    int len = ftell(p);
    fseek(p, 0, SEEK_SET);

    GLchar *src = new GLchar[len + 1];
    fread(src, 1, len , p);
    fclose(p);

    src[len] = 0;
    cout << "Done" << endl;
    return src;
}
