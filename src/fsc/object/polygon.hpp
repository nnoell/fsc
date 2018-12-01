#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <string>

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "vertices/data.hpp"
#include "object.hpp"
#include "text.hpp"

namespace fsc {
namespace object {

// The Polygon class
class Polygon : public Object {
 public:
  // Constructor
  Polygon(const vertices::Data& vertices_data, glm::vec4 color, bool wireframe, ObjectData object_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Polygon();

  // Draws the polygon object
  void ModelDraw(glm::mat4 model = {}) const override;

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
};

}  // namespace object
}  // namespace fsc