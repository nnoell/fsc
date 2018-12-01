#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// PUBLIC
#include <fsc/external.hpp>

namespace fsc {
namespace object {
namespace vertices {

// The vertices data type
struct Data {
  // The vertices array
  const float *vertices;

  // The vertices size;
  unsigned int num_vertices;

  // The stride
  unsigned int stride;
};

}  // namespace vertices
}  // namespace object
}  // namespace fsc