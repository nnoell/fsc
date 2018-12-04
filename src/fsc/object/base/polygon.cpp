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

Polygon::Polygon(const vertices::Data& vertices_data, glm::vec4 color, bool wireframe, ObjectData object_data, glm::mat4 model) :
    Simple(std::move(color), std::move(object_data), std::move(model)),
    vertices_data_(vertices_data),
    wireframe_(wireframe) {
}

Polygon::~Polygon() {
}

void Polygon::ModelDraw(glm::mat4 model) const {
  // Set the pipeline
  Pipeline::GetInstance().SetBool("is_text_", false);
  Pipeline::GetInstance().SetMat4("model_", model);
  Pipeline::GetInstance().SetVec4("color_", GetColor());

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

}  // namespace base
}  // namespace object
}  // namespace fsc