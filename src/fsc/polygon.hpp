#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <string>

// FSC
#include "external.hpp"
#include "object.hpp"
#include "text.hpp"
#include "vertices/data.hpp"

namespace fsc {

// The Polygon class
class Polygon : public Object {
 public:
  // Constructor
  Polygon(const vertices::Data& vertices_data, glm::vec4 color, bool wireframe, glm::mat4 model = {});

  // Destructor
  virtual ~Polygon();

  // Gets the current position
  glm::vec3 GetPosition() const override;

  // Resets the polygon object
  Polygon& Reset() override;

  // Scales the polygon object
  Polygon& Scale(glm::vec3 factor) override;

  // Translates the polygon object
  Polygon& Translate(glm::vec3 factor) override;

  // Rotates the polygon object
  Polygon& Rotate(float radians, glm::vec3 factor) override;

  // Draws the polygon object
  void Draw() const override;

 private:
  // Copy Constructor
  Polygon(const Polygon&) = delete;

  // Move Constructor
  Polygon(Polygon &&) = delete;

  // Copy-Assign Constructor
  Polygon& operator=(const Polygon&) = delete;

  // Move-Assign Constructr
  Polygon& operator=(Polygon &&) = delete;

 private:
  // The vertices data
  const vertices::Data& vertices_data_;

  // The color
  glm::vec4 color_;

  // Whether it is in wireframe mode or not
  bool wireframe_;

  // The initial model matrix (position)
  glm::mat4 model_;
};

}  // namespace fsc