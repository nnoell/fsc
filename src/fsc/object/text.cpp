//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "vertices/font.hpp"
#include "text.hpp"
#include "../pipeline.hpp"

namespace fsc {
namespace object {

Text::Text(std::string text, glm::vec4 color, glm::mat4 model, TextFormat format) :
    Object(),
    text_(std::move(text)),
    color_(std::move(color)),
    model_(std::move(model)),
    format_(std::move(format)) {
}

Text::~Text() {
}

glm::vec3 Text::GetPosition() const {
  return model_ * glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};
}

Text& Text::Reset() {
  model_ = glm::mat4 {};
  return *this;
}

Text& Text::Scale(glm::vec3 factor) {
  model_ = glm::scale(model_, std::move(factor));
  return *this;
}

Text& Text::Translate(glm::vec3 position) {
  model_ = glm::translate(model_, std::move(position));
  return *this;
}

Text& Text::Rotate(float radians, glm::vec3 axes) {
  model_ = glm::rotate(model_, radians, std::move(axes));
  return *this;
}

void Text::Draw() const {
    // Set pipeline
  Pipeline::GetInstance().SetBool("is_text_", true);
  Pipeline::GetInstance().SetVec4("color_", color_);

  // Configure OpenGL to render text
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // Generate VAO and VBO
  GLuint vao = 0, vbo = 0;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  // Make a copy of the model
  glm::mat4 model_local = model_;
  model_local = glm::scale(model_local, format_.scale);
  model_local = glm::rotate(model_local, format_.radians, format_.axes);
  glm::vec3 position_local = format_.position;

  // Render each character
  for (auto&& c : text_) {
    const vertices::CharData& char_data = vertices::Font::GetInstance().GetCharData(c);

    // Bind VAO and VBO
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Configure Buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * char_data.stride * char_data.num_vertices, NULL, GL_DYNAMIC_DRAW);

    // Configure Vertex
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, char_data.stride * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);
    // Configure Extra
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, char_data.stride * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // Configure VBO
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * char_data.stride * char_data.num_vertices, char_data.vertices.get());

    // Activate render state
    glActiveTexture(GL_TEXTURE0);

    // Bind texture
    glBindTexture(GL_TEXTURE_2D, char_data.texture);

    // Set the model
    Pipeline::GetInstance().SetMat4("model_", glm::translate(model_local, position_local));

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, char_data.num_vertices);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Advance the cursor for next glyph
    position_local.x += char_data.next_position;
  }

  // Delete VAO and VBO
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

}  // namespace object
}  // namespace fsc