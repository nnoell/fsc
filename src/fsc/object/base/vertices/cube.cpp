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
  // Back face
  -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // Bottom-left
  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // top-right
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom-right
  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // top-right
  -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // bottom-left
  -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // top-left
  // Front face
  -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // bottom-left
  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, // bottom-right
  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, // top-right
  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, // top-right
  -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // top-left
  -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // bottom-left
  // Left face
  -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // top-right
  -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // top-left
  -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // bottom-left
  -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // bottom-left
  -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // bottom-right
  -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // top-right
  // Right face
  1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // top-left
  1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // bottom-right
  1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // top-right
  1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // bottom-right
  1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // top-left
  1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // bottom-left
  // Bottom face
  -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // top-right
  1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // top-left
  1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // bottom-left
  1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // bottom-left
  -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // bottom-right
  -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // top-right
  // Top face
  -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // top-left
  1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // bottom-right
  1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // top-right
  1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // bottom-right
  -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // top-left
  -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f  // bottom-left
};

const Data& GetCube() {
  static const Data cube_data = { cube_vertices_, 36, 6 };
  return cube_data;
}

}  // namespace vertices
}  // namespace base
}  // namespace object
}  // namespace fsc