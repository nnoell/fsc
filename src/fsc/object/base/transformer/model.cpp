//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "model.hpp"

namespace fsc {
namespace object {
namespace base {
namespace transformer {

Model::Model(glm::mat4 model) :
  Transformer("model"),
  model_(std::move(model)) {
}

Model::~Model() {
}

Model::Model(const Model& other) :
  Transformer(other),
  model_(other.model_) {
}

Model::Model(Model&& other) :
  Transformer(std::move(other)),
  model_(std::move(other.model_)) {
}

Model& Model::operator=(const Model& other) {
  Transformer::operator=(other);
  model_ = other.model_;
  return *this;
}

Model& Model::operator=(Model&& other) {
  Transformer::operator=(std::move(other));
  model_ = std::move(other.model_);
  return *this;
}

glm::mat4 Model::Transform(const glm::mat4& model) const {
  return model_ * model;  // Beware that matrix multiplication is not commutative
}

}  // namespace transformer
}  // namespace base
}  // namespace object
}  // namespace fsc