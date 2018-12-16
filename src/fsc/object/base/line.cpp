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

Line::Line(std::vector<glm::vec3> points, glm::vec4 color,
    transformer::Translate translate, transformer::Scale scale, transformer::Rotate rotate, transformer::Model model) :
    Simple(std::move(color), std::move(translate), std::move(scale), std::move(rotate), std::move(model)),
    points_(std::move(points)),
    num_vertices_(0),
    vertices_(nullptr) {
  Update();
}

Line::~Line() {
}

void Line::Update() {
  // Return if there are no points
  if (points_.size() == 0)
    return;

  // Update the number of vertices
  num_vertices_ = points_.size() * 6;

  // Allocate the vertices array
  vertices_ = std::shared_ptr<float []> {new float[num_vertices_], std::default_delete<float[]>()};

  // Set the vertices array
  unsigned int i = 0;
  for (auto&& p : points_) {
    vertices_[i++] = p.x;
    vertices_[i++] = p.y;
    vertices_[i++] = p.z;
    vertices_[i++] = 1.0f;
    vertices_[i++] = 0.0f;
    vertices_[i++] = 0.0f;
  }
}

void Line::SetPoints(std::vector<glm::vec3> points) {
  points_ = std::move(points);
  Update();
}

void Line::Draw() const {
  // Return if there are no points
  if (points_.size() == 0)
    return;

  // Set the pipeline
  Pipeline::GetInstance().SetBool("is_text_", false);
  Pipeline::GetInstance().SetMat4("model_", GetModel());
  Pipeline::GetInstance().SetVec4("color_", GetColor());

  // Configure OpenGL
  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // The stride of the vertex
  constexpr unsigned int stride = 6;

  // Generate
  unsigned int vao = 0, vbo = 0;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  // Bind VAO
  glBindVertexArray(vao);

  // Bind and set VBO
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices_, vertices_.get(), GL_STATIC_DRAW);

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