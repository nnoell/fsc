#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <memory>

// PUBLIC
#include <fsc/external.hpp>

namespace fsc {
namespace object {
namespace vertices {

// The polygon data type
struct Data {
  // The vertices array
  const float *vertices;

  // The vertices size;
  unsigned int num_vertices;

  // The stride
  unsigned int stride;
};

// The char data type
struct CharData {
  // The vertices
  std::shared_ptr<const float []> vertices;

  // The number of vertices
  unsigned int num_vertices;

  // The stride
  unsigned int stride;

  // The position for the next character
  float next_position;

  // The texture
  unsigned int texture;
};

}  // namespace vertices
}  // namespace object
}  // namespace fsc