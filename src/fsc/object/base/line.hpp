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
  Line(std::vector<glm::vec3> points, glm::vec4 color,
      transformer::Translate translate = {}, transformer::Scale scale = {}, transformer::Rotate rotate = {}, transformer::Model model = {});

  // Destructor
  virtual ~Line();

  // Sets the points
  void SetPoints(std::vector<glm::vec3> points);

  // Draws the line
  void Draw() const override;

 private:
  // Updates the line
  void Update();

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
  // The points of the line
  std::vector<glm::vec3> points_;

  // The number of vertices
  unsigned int num_vertices_;

  // The vertices of the line
  std::shared_ptr<float []> vertices_;

  // The Vertex Array Object
  unsigned int vao_;

  // The Vertex Buffer Object
  unsigned int vbo_;
};

}  // namespace base
}  // namespace object
}  // namespace fsc