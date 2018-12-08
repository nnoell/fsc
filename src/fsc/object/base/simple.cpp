//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "simple.hpp"

namespace fsc {
namespace object {
namespace base {

Simple::Simple(glm::vec4 color, TransformData transform_data, glm::mat4 model) :
    Object(std::move(transform_data), std::move(model)),
    color_(std::move(color)) {
}

Simple::~Simple() {
}

const bool Simple::IsComplex() const {
  return false;
}

glm::vec4 Simple::GetColor() const {
  return color_;
}

void Simple::SetColor(glm::vec4 color) {
  color_ = color;
}

glm::vec3 Simple::GetModelVertexMiddle(const glm::mat4& model) const {
  return model * glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};
}

glm::vec3 Simple::GetModelVertexMax(const glm::mat4& model) const {
  return model * glm::vec4 {1.0f, 1.0f, 1.0f, 1.0f};
}

glm::vec3 Simple::GetModelVertexMin(const glm::mat4& model) const {
  return model * glm::vec4 {-1.0f, -1.0f, -1.0f, 1.0f};
}

}  // namespace base
}  // namespace object
}  // namespace fsc