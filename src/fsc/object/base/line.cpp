//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "line.hpp"
#include "../../pipeline.hpp"

namespace fsc {
namespace object {
namespace base {

Line::Line(std::vector<glm::vec3> points, glm::vec4 color, TransformData transform_data, glm::mat4 model) :
    Simple(std::move(color), std::move(transform_data), std::move(model)),
    num_vertices_(points.size() * 3 * 6),
    vertices_(new float[num_vertices_], std::default_delete<float[]>()) {
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

void Line::ModelDraw(const glm::mat4& model) const {
  // Set the pipeline
  Pipeline::GetInstance().SetBool("is_text_", false);
  Pipeline::GetInstance().SetMat4("model_", model);
  Pipeline::GetInstance().SetVec4("color_", GetColor());

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

}  // namespace base
}  // namespace object
}  // namespace fsc