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
    vertices_(nullptr),
    vao_(0),
    vbo_(0) {
  Update();
}

Line::~Line() {
  // Release VAO and VBO
  if (vbo_)
    glDeleteBuffers(1, &vbo_);
  if (vao_)
    glDeleteVertexArrays(1, &vao_);
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
  Pipeline::GetInstance().SetVec4("object_color_", GetColor());
  
  // Draw
  glBindVertexArray(vao_);
  glDrawArrays(GL_LINES, 0, num_vertices_);
  glBindVertexArray(0);
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

  // Release VAO and VBO
  if (vbo_)
    glDeleteBuffers(1, &vbo_);
  if (vao_)
    glDeleteVertexArrays(1, &vao_);

  // Generate VAO and VBO
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);

  // Bind VAO
  glBindVertexArray(vao_);

  // Bind and set VBO
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices_, vertices_.get(), GL_STATIC_DRAW);

  // Configure Vertex
  constexpr unsigned int stride = 6;
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)0);
  glEnableVertexAttribArray(0);
  // Configure Extra
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(4 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

}  // namespace base
}  // namespace object
}  // namespace fsc