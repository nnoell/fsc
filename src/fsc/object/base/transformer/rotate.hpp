#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "transformer.hpp"

namespace fsc {
namespace object {
namespace base {
namespace transformer {

// The Rotate class
class Rotate : public Transformer {
 public:
  // Constructor
  Rotate(float degrees = 0.0f, glm::vec3 axes = {1.0f, 1.0f, 1.0f});

  // Destructor
  virtual ~Rotate();

  // Copy Constructor
  Rotate(const Rotate& other);

  // Move Constructor
  Rotate(Rotate&& other);

  // Copy-Assign Constructor
  Rotate& operator=(const Rotate& other);

  // Move-Assign Translate
  Rotate& operator=(Rotate&& other);

  // Transforms a model matrix with this transformer
  glm::mat4 Transform(const glm::mat4& model = {}) const override;

 private:
  // The degrees to rotate
  float degrees_;

  // The axes to rotate
  glm::vec3 axes_;
};

}  // namespace transformer
}  // namespace base
}  // namespace object
}  // namespace fsc