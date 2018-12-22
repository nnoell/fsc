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

// The Translate class
class Translate : public Transformer {
 public:
  // Constructor
  Translate(glm::vec3 position = {0.0f, 0.0f, 0.0f});

  // Destructor
  virtual ~Translate();

  // Copy Constructor
  Translate(const Translate& other);

  // Move Constructor
  Translate(Translate&& other);

  // Copy-Assign Constructor
  Translate& operator=(const Translate& other);

  // Move-Assign Translate
  Translate& operator=(Translate&& other);

  // Gets the position
  const glm::vec3& GetPosition() const;

  // Transforms a model matrix with this transformer
  glm::mat4 Transform(const glm::mat4& model = {}) const override;

 private:
  // The final position
  glm::vec3 position_;
};

}  // namespace transformer
}  // namespace base
}  // namespace object
}  // namespace fsc