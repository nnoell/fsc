//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "square.hpp"

namespace fsc {
namespace vertices {

// The square vertices
float square_vertices_[] = {
  // First triangle
  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

  // Second triangle
  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f
};

const Data& GetSquare() {
  static const Data& square_data {square_vertices_, 6, 6};
  return square_data;
}

}  // vertices
}  // fsc