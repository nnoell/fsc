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
namespace base {

// The Ascii class
class Ascii final : public Complex {
 public:
  // Constructor
  Ascii(std::string ascii, glm::vec4 color = glm::vec4 {0.2, 0.8f, 0.8f, 1.0f},
    transformer::Translate translate = {}, transformer::Scale scale = {}, transformer::Rotate rotate = {}, transformer::Model model = {});

  // Destructor
  virtual ~Ascii();

  // Gets the Ascii
  std::string GetAscii() const;

  // Sets the Ascii
  void SetAscii(std::string ascii);

 private:
  // Updates the Ascii text
  void Update();

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

  // The color
  glm::vec4 color_;
};

}  // namespace base
}  // namespace object
}  // namespace fsc