//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "character.hpp"
#include "../../pipeline.hpp"

namespace fsc {
namespace object {
namespace base {

Character::Character(char character, glm::vec4 color, ObjectData object_data, glm::mat4 model) :
    Simple(std::move(color), std::move(object_data), std::move(model)),
    character_(character) {
}

Character::~Character() {
}

char Character::GetCharacter() const {
  return character_;
}


void Character::SetCharacter(char character) {
  character_ = character;
}

const vertices::CharData& Character::GetData() const {
  return vertices::Font::GetInstance().GetCharData(character_);
}

void Character::ModelDraw(glm::mat4 model) const {
  // Get the char data
  const vertices::CharData& char_data = vertices::Font::GetInstance().GetCharData(character_);

  // Set the pipeline
  Pipeline::GetInstance().SetBool("is_text_", true);
  Pipeline::GetInstance().SetMat4("model_", model);
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

  // Draw
  glDrawArrays(GL_TRIANGLES, 0, char_data.num_vertices);

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