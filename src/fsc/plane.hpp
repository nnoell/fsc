#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <string>

// FSC
#include "external.hpp"
#include "complex.hpp"

namespace fsc {

// The Directory class
class Plane final : public Complex {
 public:
  // Constructor
  Plane(unsigned int width, unsigned int height, float scale);

  // Destructor
  virtual ~Plane();

 private:
  // Copy Constructor
  Plane(const Plane&) = delete;

  // Move Constructor
  Plane(Plane &&) = delete;

  // Copy-Assign Constructor
  Plane& operator=(const Plane&) = delete;

  // Move-Assign Constructr
  Plane& operator=(Plane &&) = delete;

 private:
  // The width of the plane
  const unsigned int width_;

  // The height of the plane
  const unsigned int height_;

  // The scale of the plane
  float scale_;
};

}  // namespace fsc