//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "vertices/font.hpp"
#include "text.hpp"
#include "../pipeline.hpp"

namespace fsc {
namespace object {

Text::Text(std::string text, glm::vec4 color, ObjectData object_data, glm::mat4 model) :
    Object(true, std::move(object_data)),
    text_(std::move(text)),
    color_(std::move(color)) {
}

Text::~Text() {
}

void Text::ModelDraw(glm::mat4 model) const {
    // Set pipeline
  Pipeline::GetInstance().SetBool("is_text_", true);
  Pipeline::GetInstance().SetVec4("color_", color_);

  // Configure OpenGL to render text
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // Generate VAO and VBO
  GLuint vao = 0, vbo = 0;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  // Make the model transformations based on the object data
  const ObjectData& object_data = GetObjectData();
  model = glm::scale(model, object_data.scale);
  model = glm::rotate(model, object_data.radians, object_data.axes);
  glm::vec3 position_local = object_data.position;

  // Render each character
  for (auto&& c : text_) {
    const vertices::CharData& char_data = vertices::Font::GetInstance().GetCharData(c);

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

    // Set the model
    Pipeline::GetInstance().SetMat4("model_", glm::translate(model, position_local));

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, char_data.num_vertices);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Advance the cursor for next glyph
    position_local.x += char_data.next_position;
  }

  // Delete VAO and VBO
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

}  // namespace object
}  // namespace fsc