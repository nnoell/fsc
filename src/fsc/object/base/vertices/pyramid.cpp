//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "pyramid.hpp"

namespace fsc {
namespace object {
namespace base {
namespace vertices {

// The pyramid vertices
static const float pyramid_vertices_[] = {
  // Front
  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

  // Right
  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
 
  // Back
  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
 
  // Left
  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

  // Bottom 1
  -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,

  // Bottom 2
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f
};

const Data& GetPyramid() {
  static const Data pyramid_data {pyramid_vertices_, 18, 6};
  return pyramid_data;
}

}  // namespace vertices
}  // namespace base
}  // namespace object
}  // namespace fsc