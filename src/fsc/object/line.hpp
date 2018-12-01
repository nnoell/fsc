#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <vector>
#include <memory>

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "object.hpp"

namespace fsc {
namespace object {

// The Line class
class Line final : public Object {
 public:
  // Constructor
  Line(std::vector<glm::vec3> points, glm::vec4 color, glm::mat4 model = {});

  // Destructor
  virtual ~Line();

  // Gets the current position
  glm::vec3 GetPosition() const override;

  // Resets the object
  Object& Reset() override;

  // Scales the object
  Object& Scale(glm::vec3 factor) override;

  // Translates the object
  Object& Translate(glm::vec3 position) override;

  // Rotates the object
  Object& Rotate(float radians, glm::vec3 axes) override;

  // Draw the line
  void Draw() const override;

 private:
  // Copy Constructor
  Line(const Line&) = delete;

  // Move Constructor
  Line(Line &&) = delete;

  // Copy-Assign Constructor
  Line& operator=(const Line&) = delete;

  // Move-Assign Constructr
  Line& operator=(Line &&) = delete;

 private:
  // The number of vertices
  unsigned int num_vertices_;

  // The vertices of the line
  std::shared_ptr<float []> vertices_;

  // The color of the line
  glm::vec4 color_;

  // The model matrix
  glm::mat4 model_;
};

}  // namespace object
}  // namespace fsc