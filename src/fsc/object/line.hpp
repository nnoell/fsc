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

namespace fsc {
namespace object {

// The Line class
class Line final {
 public:
  // Constructor
  Line(std::vector<glm::vec3> points, glm::vec4 color);

  // Destructor
  virtual ~Line();

  // Draw the line
  void Draw() const;

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
};

}  // namespace object
}  // namespace fsc