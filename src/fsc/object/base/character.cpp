//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "vertices/font.hpp"
#include "character.hpp"
#include "../../pipeline.hpp"

namespace fsc {
namespace object {
namespace base {

Character::Character(char character, glm::vec4 color,
      transformer::Translate translate, transformer::Scale scale, transformer::Rotate rotate, transformer::Model model) :
    Simple(std::move(color), std::move(translate), std::move(scale), std::move(rotate), std::move(model)),
    character_(character),
    vertices_data_(vertices::Font::GetInstance().GetCharVerticesData(character_)) {
}

Character::~Character() {
}

char Character::GetCharacter() const {
  return character_;
}


void Character::SetCharacter(char character) {
  character_ = character;
  vertices_data_ = vertices::Font::GetInstance().GetCharVerticesData(character_);
}

float Character::GetNextPosition() const {
  return vertices_data_->next_position;
}

void Character::Draw() const {
  // Set the pipeline
  Pipeline::GetInstance().SetBool("is_text_", true);
  Pipeline::GetInstance().SetMat4("model_", GetModel());
  Pipeline::GetInstance().SetVec4("color_", GetColor());

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
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_data_->stride * vertices_data_->num_vertices, NULL, GL_DYNAMIC_DRAW);

  // Configure Vertex
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertices_data_->stride * sizeof(GLfloat), (void *)0);
  glEnableVertexAttribArray(0);
  // Configure Extra
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertices_data_->stride * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // Configure VBO
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertices_data_->stride * vertices_data_->num_vertices, vertices_data_->vertices.get());

  // Activate render state
  glActiveTexture(GL_TEXTURE0);

  // Bind texture
  glBindTexture(GL_TEXTURE_2D, vertices_data_->texture);

  // Draw
  glDrawArrays(GL_TRIANGLES, 0, vertices_data_->num_vertices);

  // Unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);

  // Unbind VAO and VBO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Delete VAO and VBO
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

}  // namespace base
}  // namespace object
}  // namespace fsc