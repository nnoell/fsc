//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <memory>

// FSC
#include "base/vertices/square.hpp"
#include "base/polygon.hpp"
#include "plane.hpp"

namespace fsc {
namespace object {

Plane::Plane(unsigned int width, unsigned int height, float scale, base::ObjectData object_data, glm::mat4 model) :
    Complex({}, std::move(object_data), std::move(model)),
    width_(std::move(width)),
    height_(std::move(height)),
    scale_(std::move(scale)) {
  for (unsigned int i = 0; i < width; ++i)
    for (unsigned int j = 0; j < height; ++j)
      AddObject(std::make_shared<base::Polygon>(base::vertices::GetSquare(), glm::vec4 {0.3f, 0.3f, 0.3f, 0.3f}, true, base::ObjectData {{(i * 5), (j * 5), 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}}));
}

Plane::~Plane() {
}

}  // namespace object
}  // namespace fsc