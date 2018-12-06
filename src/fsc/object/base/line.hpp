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
#include "simple.hpp"

namespace fsc {
namespace object {
namespace base {

// The Line class
class Line final : public Simple {
 public:
  // Constructor
  Line(std::vector<glm::vec3> points, glm::vec4 color, ObjectData object_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Line();

  // Draw the line
  void ModelDraw(const glm::mat4& model = {}) const override;

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
};

}  // namespace base
}  // namespace object
}  // namespace fsc