//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "translate.hpp"

namespace fsc {
namespace object {
namespace base {
namespace transformer {

Translate::Translate(glm::vec3 position) :
  Transformer("translate"),
  position_(std::move(position)) {
}

Translate::~Translate() {
}

Translate::Translate(const Translate& other) :
  Transformer(other),
  position_(other.position_) {
}

Translate::Translate(Translate&& other) :
  Transformer(std::move(other)),
  position_(std::move(other.position_)) {
}

Translate& Translate::operator=(const Translate& other) {
  Transformer::operator=(other);
  position_ = other.position_;
  return *this;
}

Translate& Translate::operator=(Translate&& other) {
  Transformer::operator=(std::move(other));
  position_ = std::move(other.position_);
  return *this;
}

const glm::vec3& Translate::GetPosition() const {
  return position_;
}

glm::mat4 Translate::Transform(const glm::mat4& model) const {
  return glm::translate(model, position_);  
}

}  // namespace transformer
}  // namespace base
}  // namespace object
}  // namespace fsc