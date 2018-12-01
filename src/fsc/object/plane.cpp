//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <memory>

// FSC
#include "plane.hpp"
#include "polygon.hpp"
#include "vertices/square.hpp"

namespace fsc {
namespace object {

Plane::Plane(unsigned int width, unsigned int height, float scale, ObjectData object_data, glm::mat4 model) :
    Complex({}, std::move(object_data), std::move(model)),
    width_(std::move(width)),
    height_(std::move(height)),
    scale_(std::move(scale)) {
  for (int i = 0; i < width; ++i)
    for (int j = 0; j < height; ++j)
      AddObject(std::make_shared<Polygon>(vertices::GetSquare(), glm::vec4 {0.3f, 0.3f, 0.3f, 0.3f}, true, ObjectData {{(i * 5), (j * 5), 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}}));
}

Plane::~Plane() {
}

}  // namespace object
}  // namespace fsc