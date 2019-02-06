#version 330 core

in vec2 TextCoords;
out vec4 FragColor;

uniform bool is_text_;
uniform sampler2D text_texture_;
uniform vec4 object_color_;

void main() {
  if (is_text_) {
    FragColor = object_color_ * vec4(1.0, 1.0, 1.0, texture(text_texture_, TextCoords).r);
  } else {
	  FragColor = object_color_;
  }
}