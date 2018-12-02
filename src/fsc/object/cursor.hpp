#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <string>

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "complex.hpp"

namespace fsc {
namespace object {

// The Cursor class
class Cursor final : public Complex {
 public:
  // Constructor
  Cursor(ObjectData object_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Cursor();

 private:
  // Copy Constructor
  Cursor(const Cursor&) = delete;

  // Move Constructor
  Cursor(Cursor &&) = delete;

  // Copy-Assign Constructor
  Cursor& operator=(const Cursor&) = delete;

  // Move-Assign Constructr
  Cursor& operator=(Cursor &&) = delete;
};

}  // namespace object
}  // namespace fsc