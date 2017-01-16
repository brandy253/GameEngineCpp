#include "Shader.h"

Shader::Shader()
{
    vertexShader = 0;
}

Shader::~Shader()
{
    //dtor
}

void Shader::createVertexShader() {
    cout << "Creating vertex shader object...";
    int id = glCreateShader( GL_VERTEX_SHADER );
    if(id == 0) {
        cout << "Error occured while creating vertex shader object" << endl;
        return;
    }
    vertexShader = id;
    cout << "Done" << endl;
}

void Shader::compileVertexShader(char *src) {
    cout << "Compiling vertex shader...";
    GLchar* codeArray[] = {src};
    glShaderSource( vertexShader, 1, codeArray, NULL );
    glCompileShader( vertexShader );

    GLint result;
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &result );

    if(result == GL_FALSE) {
        cout << endl << "Vertex shader compilation failed" << endl;
        GLint logLen;
        glGetShaderiv( vertexShader, GL_INFO_LOG_LENGTH, &logLen );
        if(logLen > 0) {
            char *log = (char*)malloc(logLen);
            GLsizei written;
            glGetShaderInfoLog(vertexShader, logLen, &written, log);
            cout << log << endl;
            free(log);
        }
        return;
    }
    cout << "Done" << endl;
}

void Shader::createFragmentShader() {
    cout << "Creating fragment shader object..";
    int id = glCreateShader( GL_FRAGMENT_SHADER );
    if(id == 0) {
        cout << "Error occured while creating fragment shader object" << endl;
        return;
    }
    fragmentShader = id;
    cout << "Done" << endl;
}

void Shader::compileFragmentShader(char* src) {
    cout << "Compiling fragment shader...";
    GLchar* codeArray[] = {src};
    glShaderSource( fragmentShader, 1, codeArray, NULL );
    glCompileShader(fragmentShader);

    GLint result;
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {
        cout << endl << "Fragment shader compilation failed" << endl;
        GLint logLen;
        glGetShaderiv( fragmentShader, GL_INFO_LOG_LENGTH, &logLen);
        if(logLen) {
            char* log = (char*)malloc(logLen);
            GLsizei written;
            glGetShaderInfoLog(fragmentShader, logLen, &written, log);
            cout << log << endl;
            free(log);
        }
        return;
    }
    cout << "Done" << endl;
}

void Shader::build() {
    cout << "Linking shader program...";
    GLuint programHandle = glCreateProgram();
    if(programHandle == 0) {
        cout << "Error while creating program object" << endl;
        return;
    }
    glBindAttribLocation(programHandle, 0, "VertexPosition");
    glBindAttribLocation(programHandle, 1, "VertexColor");

    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);

    glLinkProgram(programHandle);

    GLint status;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        cout << "Failed to link shader program" << endl;
        GLint logLen;
        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);
        if(logLen) {
            char *log = (char*)malloc(logLen);
            GLsizei written;
            glGetProgramInfoLog(programHandle, logLen, &written, log);
            cout << log << endl;
            free(log);
        }
        return;
    }
    glUseProgram(programHandle);
    cout << "Done" << endl;
}
