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

Simple::Simple(glm::vec4 color, transformer::Translate translate, transformer::Scale scale, transformer::Rotate rotate, transformer::Model model) :
    Object(std::move(translate), std::move(scale), std::move(rotate), std::move(model)),
    model_(),
    color_(std::move(color)) {
  // Refresh the model matrix
  RefreshModel();
}

Simple::~Simple() {
}

const glm::mat4 Simple::GetModel() const {
  return model_;
}

glm::vec4 Simple::GetColor() const {
  return color_;
}

void Simple::SetColor(glm::vec4 color) {
  color_ = std::move(color);
}

glm::vec3 Simple::GetVertexMax() const {
  return model_ * glm::vec4 {1.0f, 1.0f, 1.0f, 1.0f};
}

glm::vec3 Simple::GetVertexMin() const {
  return model_ * glm::vec4 {-1.0f, -1.0f, -1.0f, 1.0f};
}

void Simple::RefreshModel() {
  // Order maters
  const glm::mat4 modeled = GetTransformerModel().Transform({});
  const glm::mat4 rotated = GetTransformerRotate().Transform(modeled);
  const glm::mat4 scaled = GetTransformerScale().Transform(rotated);
  model_ = GetTransformerTranslate().Transform(scaled);
}

}  // namespace base
}  // namespace object
}  // namespace fsc