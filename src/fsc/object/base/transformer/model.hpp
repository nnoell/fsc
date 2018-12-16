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

// The Model class
class Model : public Transformer {
 public:
  // Constructor
  Model(glm::mat4 model = {});

  // Destructor
  virtual ~Model();

  // Copy Constructor
  Model(const Model& other);

  // Move Constructor
  Model(Model&& other);

  // Copy-Assign Constructor
  Model& operator=(const Model& other);

  // Move-Assign Translate
  Model& operator=(Model&& other);

  // Transforms a model matrix with this transformer
  glm::mat4 Transform(const glm::mat4& model = {}) const override;

 private:
  // The model
  glm::mat4 model_;
};

}  // namespace transformer
}  // namespace base
}  // namespace object
}  // namespace fsc