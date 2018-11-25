//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "polygon.hpp"
#include "pipeline.hpp"

namespace fsc {

Polygon::Polygon(const vertices::Data& vertices_data, glm::vec4 color, bool wireframe, glm::mat4 model) :
    Object(),
    vertices_data_(vertices_data),
    color_(std::move(color)),
    wireframe_(wireframe),
    model_(std::move(model)) {
}

Polygon::~Polygon() {
}

glm::vec3 Polygon::GetPosition() const {
  return model_ * glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};
}

Polygon& Polygon::Reset() {
  model_ = glm::mat4 {};
  return *this;
}

Polygon& Polygon::Scale(glm::vec3 factor) {
  model_ = glm::scale(model_, factor);
  return *this;
}

Polygon& Polygon::Translate(glm::vec3 position) {
  model_ = glm::translate(model_, position);  
  return *this;
}

Polygon& Polygon::Rotate(float radians, glm::vec3 factor) {
  model_ = glm::rotate(model_, radians, factor);  
  return *this;
}

void Polygon::Draw() const {
  // Set the pipeline
  Pipeline::GetInstance().SetBool("is_text_", false);
  Pipeline::GetInstance().SetMat4("model_", model_);
  Pipeline::GetInstance().SetVec4("color_", color_);

  // Configure OpenGL
  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);
  if (wireframe_)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // Generate
  unsigned int vao = 0, vbo = 0;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  // Bind VAO
  glBindVertexArray(vao);

  // Bind and set VBO
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_data_.stride * vertices_data_.num_vertices, vertices_data_.vertices, GL_STATIC_DRAW);

  // Configure Vertex
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * vertices_data_.stride, (void*)0);
  glEnableVertexAttribArray(0);
  // Configure Extra
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * vertices_data_.stride, (void*)(4 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Draw
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, vertices_data_.num_vertices);
  glBindVertexArray(0);

  // Delete
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

}  // namespace fsc