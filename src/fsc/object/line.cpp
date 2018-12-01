//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "line.hpp"
#include "../pipeline.hpp"

namespace fsc {
namespace object {

Line::Line(std::vector<glm::vec3> points, glm::vec4 color, glm::mat4 model) :
    num_vertices_(points.size() * 3 * 6),
    vertices_(new float[num_vertices_], std::default_delete<float[]>()),
    color_(std::move(color)),
    model_(std::move(model)) {
  unsigned int i = 0;
  for (auto&& p : points) {
    vertices_[i++] = p.x;
    vertices_[i++] = p.y;
    vertices_[i++] = p.z;
    vertices_[i++] = 1.0f;
    vertices_[i++] = 0.0f;
    vertices_[i++] = 0.0f;
  }
}

Line::~Line() {
}

glm::vec3 Line::GetPosition() const {
  return model_ * glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};
}

Object& Line::Reset() {
  model_ = glm::mat4 {};
  return *this;
}

Object& Line::Scale(glm::vec3 factor) {
  model_ = glm::scale(model_, std::move(factor));
  return *this;
}

Object& Line::Translate(glm::vec3 position) {
  model_ = glm::translate(model_, std::move(position));  
  return *this;
}

Object& Line::Rotate(float radians, glm::vec3 axes) {
  model_ = glm::rotate(model_, radians, std::move(axes));
  return *this;
}

void Line::Draw() const {
  // Set the pipeline
  Pipeline::GetInstance().SetBool("is_text_", false);
  Pipeline::GetInstance().SetMat4("model_", model_);
  Pipeline::GetInstance().SetVec4("color_", color_);

  // Configure OpenGL
  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // The stride of the vertex
  constexpr float stride = 6;

  // Generate
  unsigned int vao = 0, vbo = 0;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  // Bind VAO
  glBindVertexArray(vao);

  // Bind and set VBO
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * stride * num_vertices_, vertices_.get(), GL_STATIC_DRAW);

  // Configure Vertex
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)0);
  glEnableVertexAttribArray(0);
  // Configure Extra
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(4 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Draw
  glBindVertexArray(vao);
  glDrawArrays(GL_LINES, 0, num_vertices_);
  glBindVertexArray(0);

  // Delete
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

}  // namespace object
}  // namespace fsc