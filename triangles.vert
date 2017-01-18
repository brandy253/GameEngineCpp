#version 430 core

in vec3 VertexColor;
in vec3 VertexPosition;

out vec3 Color;

uniform mat4 RotationMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 TranslationMatrix;
uniform mat4 TransformedMatrix;

void main() {
    Color = VertexColor;
    gl_Position = ProjectionMatrix * RotationMatrix * TranslationMatrix *  vec4(VertexPosition, 1.0);
}
