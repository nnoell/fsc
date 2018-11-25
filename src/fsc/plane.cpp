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

static std::shared_ptr<Object> MakeMasterObject(float scale) {
  auto master_object = std::make_shared<Polygon>(vertices::GetSquare(), glm::vec4 {0.3f, 0.3f, 0.3f, 0.3f}, true);
  master_object->Scale({scale, scale, scale}).Rotate(glm::radians(90.0f), {1.0f, 0.0f, 0.0f});
  return master_object;
}

Plane::Plane(unsigned int width, unsigned int height, float scale) :
    Complex(MakeMasterObject(scale), {}),
    width_(std::move(width)),
    height_(std::move(height)),
    scale_(std::move(scale)) {
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      // Skip the first case
      if (i == 0 && j == 0)
        continue;

      std::shared_ptr<Object> object = std::make_shared<Polygon>(vertices::GetSquare(), glm::vec4 {0.3f, 0.3f, 0.3f, 0.3f}, true);
      object->Translate({0.0f + (i * 5),  0.0f, 0.0f + (-1 * j * 5)}).Scale({scale, scale, scale}).Rotate(glm::radians(90.0f), {1.0f, 0.0f, 0.0f});
      AddObject(std::move(object));
    }
  }
}

Plane::~Plane() {
}

}  // namespace fsc