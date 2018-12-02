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

// The Ascii class
class Ascii final : public Complex {
 public:
  // Constructor
  Ascii(std::string ascii, glm::vec4 color = glm::vec4 {0.5, 1.0f, 0.0f, 1.0f}, ObjectData object_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0.0f, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Ascii();

 private:
  // Copy Constructor
  Ascii(const Ascii&) = delete;

  // Move Constructor
  Ascii(Ascii &&) = delete;

  // Copy-Assign Constructor
  Ascii& operator=(const Ascii&) = delete;

  // Move-Assign Constructr
  Ascii& operator=(Ascii &&) = delete;

 private:
  // The ascii text
  std::string ascii_;
};

}  // namespace object
}  // namespace fsc