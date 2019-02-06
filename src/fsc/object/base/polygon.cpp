//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "polygon.hpp"
#include "../../pipeline.hpp"

namespace fsc {
namespace object {
namespace base {

Polygon::Polygon(const vertices::Data& vertices_data, glm::vec4 color, bool wireframe,
    transformer::Translate translate, transformer::Scale scale, transformer::Rotate rotate, transformer::Model model) :
    Simple(std::move(color), std::move(translate), std::move(scale), std::move(rotate), std::move(model)),
    vertices_data_(vertices_data),
    wireframe_(wireframe),
    vao_(0),
    vbo_(0) {
  // Generate
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);

  // Bind VAO
  glBindVertexArray(vao_);

  // Bind and set VBO
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_data_.stride * vertices_data_.num_vertices, vertices_data_.vertices, GL_STATIC_DRAW);

  // Configure Vertex
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * vertices_data_.stride, (void*)0);
  glEnableVertexAttribArray(0);
  // Configure Extra
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * vertices_data_.stride, (void*)(4 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind VBO and VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Polygon::~Polygon() {
  // Release VAO and VBO
  if (vbo_)
    glDeleteBuffers(1, &vbo_);
  if (vao_)
    glDeleteVertexArrays(1, &vao_);
}

void Polygon::Draw() const {
  // Set the pipeline
  Pipeline::GetInstance().SetBool("is_text_", false);
  Pipeline::GetInstance().SetMat4("model_", GetModel());
  Pipeline::GetInstance().SetVec4("object_color_", GetColor());
  Pipeline::GetInstance().SetVec4("light_color_", glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

  // Configure
  if (wireframe_)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // Draw
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertices_data_.num_vertices);
  glBindVertexArray(0);
}

}  // namespace base
}  // namespace object
}  // namespace fsc