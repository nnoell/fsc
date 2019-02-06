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
    character_(std::move(character)),
    vertices_data_(vertices::Font::GetInstance().GetCharVerticesData(character_)),
    vao_(0),
    vbo_(0) {
  // Update the character
  Update();
}

Character::~Character() {
  // Release VAO and VBO
  if (vbo_)
    glDeleteBuffers(1, &vbo_);
  if (vao_)
    glDeleteVertexArrays(1, &vao_);
}

char Character::GetCharacter() const {
  return character_;
}

void Character::SetCharacter(char character) {
  character_ = character;
  vertices_data_ = vertices::Font::GetInstance().GetCharVerticesData(character_);
  Update();
}

float Character::GetNextPosition() const {
  return vertices_data_->next_position;
}

void Character::Draw() const {
  // Set the pipeline
  Pipeline::GetInstance().SetBool("is_text_", true);
  Pipeline::GetInstance().SetMat4("model_", GetModel());
  Pipeline::GetInstance().SetVec4("object_color_", GetColor());

  // Configure OpenGL to render text
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Bind texture
  glBindTexture(GL_TEXTURE_2D, vertices_data_->texture);

  // Draw
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertices_data_->num_vertices);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Character::Update() {
  // Release VAO and VBO
  if (vbo_)
    glDeleteBuffers(1, &vbo_);
  if (vao_)
    glDeleteVertexArrays(1, &vao_);

  // Generate
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);

  // Bind VAO and VBO
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

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

  // Unbind VAO and VBO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

}  // namespace base
}  // namespace object
}  // namespace fsc