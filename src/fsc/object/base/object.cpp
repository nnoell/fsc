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

glm::vec3 Object::GetVertexTop() const {
  const glm::vec3 max = GetVertexMax();
  const glm::vec3 middle = GetVertexMiddle();
  return {middle.x, max.y, middle.z};
}

glm::vec3 Object::GetVertexMiddle() const {
  return GetModelVertexMiddle(model_);
}

glm::vec3 Object::GetVertexMax() const {
  return GetModelVertexMax(model_);
}

glm::vec3 Object::GetVertexMin() const {
  return GetModelVertexMin(model_);
}

glm::vec4 Object::GetAreaDimension() const {
  const glm::vec3 max = GetVertexMax();
  const glm::vec3 diff = GetVertexMax() - GetVertexMin();
  return {max.x, max.z, diff.x, diff.z};
}

glm::mat4 Object::Transform() const {
  return ModelTransform(model_);
}

glm::mat4 Object::ModelTransform(const glm::mat4& model) const {
  glm::mat4 res = glm::scale(model, GetTransformData().scale);
  res = glm::rotate(res, GetTransformData().radians, GetTransformData().axes);
  return glm::translate(res, GetTransformData().position);
}

void Object::Draw() const {
  ModelDraw(model_);
}

}  // namespace base
}  // namespace object
}  // namespace fsc