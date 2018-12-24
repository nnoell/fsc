//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <atomic>

// FSC
#include "object.hpp"

namespace fsc {
namespace object {
namespace base {

// Gets a unique Id
static unsigned int GetUniqueId() {
  static std::atomic<unsigned int> id(0);
  return id++;
}

Object::Object(transformer::Translate translate, transformer::Scale scale, transformer::Rotate rotate, transformer::Model model) :
    id_(GetUniqueId()),
    translate_transformer_(std::move(translate)),
    scale_transformer_(std::move(scale)),
    rotate_transformer_(std::move(rotate)),
    model_transformer_(std::move(model)) {
}

Object::~Object() {
}

unsigned int Object::GetId() const {
  return id_;
}

const transformer::Translate& Object::GetTransformerTranslate() const {
  return translate_transformer_;
}

const transformer::Scale& Object::GetTransformerScale() const {
  return scale_transformer_;
}

const transformer::Rotate& Object::GetTransformerRotate() const {
  return rotate_transformer_;
}

const transformer::Model& Object::GetTransformerModel() const {
  return model_transformer_;
}

Object& Object::Translate(transformer::Translate translate) {
  translate_transformer_ = std::move(translate);
  RefreshModel();
  return *this;
}

Object& Object::Scale(transformer::Scale scale) {
  scale_transformer_ = std::move(scale);
  RefreshModel();
  return *this;
}

Object& Object::Rotate(transformer::Rotate rotate) {
  rotate_transformer_ = std::move(rotate);
  RefreshModel();
  return *this;
}

Object& Object::Model(transformer::Model model) {
  model_transformer_ = std::move(model);
  RefreshModel();
  return *this;
}

glm::vec3 Object::GetDimension() const {
  return glm::abs(GetVertexMax() - GetVertexMin());
}

glm::vec3 Object::GetVertexTop() const {
  const glm::vec3 max = GetVertexMax();
  const glm::vec3 center = GetVertexCenter();
  return {center.x, max.y, center.z};
}

glm::vec3 Object::GetVertexFront() const {
  const glm::vec3 max = GetVertexMax();
  const glm::vec3 center = GetVertexCenter();
  return {center.x, center.y, max.z};
}

glm::vec3 Object::GetVertexCenter() const {
  glm::vec3 center = GetVertexMax() + GetVertexMin();
  center /= 2.0f;
  return center;
}

}  // namespace base
}  // namespace object
}  // namespace fsc