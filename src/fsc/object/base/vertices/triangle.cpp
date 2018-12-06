//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// GLE
#include "triangle.hpp"

namespace fsc {
namespace object {
namespace base {
namespace vertices {

// The triangle vertices
const float triangle_vertices_[] = {
  -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f
};

const Data& GetTriangle() {
  static const Data triangle_data {triangle_vertices_, 3, 6};
  return triangle_data;
}

}  // namespace vertices
}  // namespace base
}  // namespace object
}  // namespace fsc