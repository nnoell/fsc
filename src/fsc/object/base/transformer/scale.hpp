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

// The Scale class
class Scale : public Transformer {
 public:
  // Constructor
  Scale(glm::vec3 factor = {1.0f, 1.0f, 1.0f});

  // Destructor
  virtual ~Scale();

  // Gets the factor
  glm::vec3 GetFactor() const;

  // Copy Constructor
  Scale(const Scale& other);

  // Move Constructor
  Scale(Scale&& other);

  // Copy-Assign Constructor
  Scale& operator=(const Scale& other);

  // Move-Assign Translate
  Scale& operator=(Scale&& other);

  // Transforms a model matrix with this transformer
  glm::mat4 Transform(const glm::mat4& model = {}) const override;

 private:
  // The scale factor
  glm::vec3 factor_;
};

}  // namespace transformer
}  // namespace base
}  // namespace object
}  // namespace fsc