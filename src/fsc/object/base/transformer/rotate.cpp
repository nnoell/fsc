//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "rotate.hpp"

namespace fsc {
namespace object {
namespace base {
namespace transformer {

Rotate::Rotate(float degrees, glm::vec3 axes) :
  Transformer("rotate"),
  degrees_(std::move(degrees)),
  axes_(std::move(axes)) {
}

Rotate::~Rotate() {
}

Rotate::Rotate(const Rotate& other) :
  Transformer(other),
  degrees_(other.degrees_),
  axes_(other.axes_) {
}

Rotate::Rotate(Rotate&& other) :
  Transformer(std::move(other)),
  degrees_(std::move(other.degrees_)),
  axes_(std::move(other.axes_)) {
}

Rotate& Rotate::operator=(const Rotate& other) {
  Transformer::operator=(other);
  degrees_ = other.degrees_;
  axes_ = other.axes_;
  return *this;
}

Rotate& Rotate::operator=(Rotate&& other) {
  Transformer::operator=(std::move(other));
  degrees_ = std::move(other.degrees_);
  axes_ = std::move(other.axes_);
  return *this;
}

glm::mat4 Rotate::Transform(const glm::mat4& model) const {
  return glm::rotate(model, glm::radians(degrees_), axes_);
}

}  // namespace transformer
}  // namespace base
}  // namespace object
}  // namespace fsc