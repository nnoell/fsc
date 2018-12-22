//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "scale.hpp"

namespace fsc {
namespace object {
namespace base {
namespace transformer {

Scale::Scale(glm::vec3 factor) :
  Transformer("scale"),
  factor_(std::move(factor)) {
}

Scale::~Scale() {
}

glm::vec3 Scale::GetFactor() const { 
  return factor_;
}

Scale::Scale(const Scale& other) :
  Transformer(other),
  factor_(other.factor_) {
}

Scale::Scale(Scale&& other) :
  Transformer(std::move(other)),
  factor_(std::move(other.factor_)) {
}

Scale& Scale::operator=(const Scale& other) {
  Transformer::operator=(other);
  factor_ = other.factor_;
  return *this;
}

Scale& Scale::operator=(Scale&& other) {
  Transformer::operator=(std::move(other));
  factor_ = std::move(other.factor_);
  return *this;
}

glm::mat4 Scale::Transform(const glm::mat4& model) const {
  return glm::scale(model, factor_);  
}

}  // namespace transformer
}  // namespace base
}  // namespace object
}  // namespace fsc