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
#include "simple.hpp"

namespace fsc {
namespace object {
namespace base {

// The Polygon class
class Polygon : public Simple {
 public:
  // Constructor
  Polygon(const vertices::Data& vertices_data, glm::vec4 color, bool wireframe,
      transformer::Translate translate = {}, transformer::Scale scale = {}, transformer::Rotate rotate = {}, transformer::Model model = {});

  // Destructor
  virtual ~Polygon();

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

  // Whether it is in wireframe mode or not
  bool wireframe_;

  // The vertex array object
  unsigned int vao_;

  // The vertex buffer object
  unsigned int vbo_;
};

}  // namespace base
}  // namespace object
}  // namespace fsc