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

Plane::Plane(unsigned int width, unsigned int height, float scale_factor, glm::vec4 color,
      base::transformer::Translate translate, base::transformer::Scale scale, base::transformer::Rotate rotate, base::transformer::Model model) :
    Complex(std::move(translate), std::move(scale), std::move(rotate), std::move(model)),
    width_(std::move(width)),
    height_(std::move(height)),
    scale_factor_(std::move(scale_factor)),
    color_(std::move(color)) {
  for (unsigned int i = 0; i < width; ++i)
    for (unsigned int j = 0; j < height; ++j)
      AddObject(std::make_shared<base::Polygon>(base::vertices::GetSquare(), color_, true, base::transformer::Translate {{i, j, 0.0f}}, base::transformer::Scale {{scale_factor_, scale_factor_, scale_factor_}}));
}

Plane::~Plane() {
}

}  // namespace object
}  // namespace fsc