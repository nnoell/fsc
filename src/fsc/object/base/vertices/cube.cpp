//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "cube.hpp"

namespace fsc {
namespace object {
namespace base {
namespace vertices {

// The cube vertices
static const float cube_vertices_[] = {
  -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,

  -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f,

  -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,

  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,

  -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,

  -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f
};

const Data& GetCube() {
  static const Data cube_data = { cube_vertices_, 36, 6 };
  return cube_data;
}

}  // namespace vertices
}  // namespace base
}  // namespace object
}  // namespace fsc