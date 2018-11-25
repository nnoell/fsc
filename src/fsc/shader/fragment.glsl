#version 330 core

in vec2 TextCoords;
out vec4 FragColor;

uniform bool is_text_;
uniform sampler2D text_texture_;
uniform vec4 color_;

void main() {
  if (is_text_) {
    FragColor = color_ * vec4(1.0, 1.0, 1.0, texture(text_texture_, TextCoords).r);
  } else {
	  FragColor = color_;
  }
}