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

Object::Object(TransformData transform_data, glm::mat4 model) :
    id_(GetUniqueId()),
    transform_data_(std::move(transform_data)),
    model_(std::move(model)) {
}

Object::~Object() {
}

unsigned int Object::GetId() const {
  return id_;
}

const TransformData& Object::GetTransformData() const {
  return transform_data_;
}

void Object::SetTransformData(TransformData transform_data) {
  transform_data_ = std::move(transform_data);
}

glm::vec3 Object::GetPosition() const {
  return model_ * ModelTransform({}) * glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};
}

glm::vec3 Object::GetPositionMax() const {
  return model_ * ModelTransform({}) * glm::vec4 {1.0f, 1.0f, 1.0f, 1.0f};
}

glm::vec3 Object::GetPositionMin() const {
  return model_ * ModelTransform({}) * glm::vec4 {-1.0f, -1.0f, -1.0f, 1.0f};
}

glm::mat4 Object::Transform() {
  model_ = ModelTransform(model_);
  return model_;
}
 
glm::mat4 Object::ModelTransform(const glm::mat4& model) const {
  glm::mat4 res = glm::scale(model, transform_data_.scale);
  res = glm::rotate(res, transform_data_.radians, transform_data_.axes);
  return glm::translate(res, transform_data_.position);
}

void Object::Draw() const {
  ModelDraw(model_);
}

}  // namespace base
}  // namespace object
}  // namespace fsc