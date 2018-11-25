#version 330 core

layout (location = 0) in vec4 Vertex;
layout (location = 1) in vec2 Extra;
out vec2 TextCoords;

uniform mat4 model_;
uniform mat4 view_;
uniform mat4 projection_;

void main() {
  gl_Position = projection_ * view_ * model_ * Vertex;
  TextCoords = Extra;
}