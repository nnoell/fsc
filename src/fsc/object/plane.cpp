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

Plane::Plane(unsigned int width, unsigned int height, float scale, glm::vec4 color, base::TransformData transform_data, glm::mat4 model) :
    Complex({}, std::move(transform_data), std::move(model)),
    width_(std::move(width)),
    height_(std::move(height)),
    scale_(std::move(scale)),
    color_(std::move(color)) {
  for (unsigned int i = 0; i < width; ++i)
    for (unsigned int j = 0; j < height; ++j)
      AddObject(std::make_shared<base::Polygon>(base::vertices::GetSquare(), color_, true, base::TransformData {{i, j, 0.0f}, {scale_, scale_, scale_}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}}));
}

Plane::~Plane() {
}

}  // namespace object
}  // namespace fsc