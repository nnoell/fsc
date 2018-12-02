//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "character.hpp"
#include "../pipeline.hpp"

namespace fsc {
namespace object {

Character::Character(char character, glm::vec4 color, ObjectData object_data, glm::mat4 model) :
    Object(false, std::move(object_data), std::move(model)),
    char_data_(vertices::Font::GetInstance().GetCharData(character)),
    color_(std::move(color)) {
}

Character::~Character() {
}

const vertices::CharData& Character::GetData() const {
  return char_data_;
}

void Character::ModelDraw(glm::mat4 model) const {
  // Set the pipeline
  Pipeline::GetInstance().SetBool("is_text_", true);
  Pipeline::GetInstance().SetMat4("model_", model);
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

  // Bind VAO and VBO
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // Configure Buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * char_data_.stride * char_data_.num_vertices, NULL, GL_DYNAMIC_DRAW);

  // Configure Vertex
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, char_data_.stride * sizeof(GLfloat), (void *)0);
  glEnableVertexAttribArray(0);
  // Configure Extra
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, char_data_.stride * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // Configure VBO
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * char_data_.stride * char_data_.num_vertices, char_data_.vertices.get());

  // Activate render state
  glActiveTexture(GL_TEXTURE0);

  // Bind texture
  glBindTexture(GL_TEXTURE_2D, char_data_.texture);

  // Draw
  glDrawArrays(GL_TRIANGLES, 0, char_data_.num_vertices);

  // Unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);

  // Unbind VAO and VBO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Delete VAO and VBO
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

}  // namespace object
}  // namespace fsc