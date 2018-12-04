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

Object::Object(ObjectData object_data, glm::mat4 model) :
    id_(GetUniqueId()),
    object_data_(std::move(object_data)),
    model_(std::move(model)) {
}

Object::~Object() {
}

unsigned int Object::GetId() const {
  return id_;
}

const ObjectData& Object::GetObjectData() const {
  return object_data_;
}

void Object::SetObjectData(ObjectData object_data) {
  object_data_ = std::move(object_data);
}

glm::vec3 Object::GetPosition() const {
  return model_ * glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};
}

Object& Object::Scale(glm::vec3 factor) {
  model_ = glm::scale(model_, factor);
  return *this;
}

Object& Object::Translate(glm::vec3 position) {
  model_ = glm::translate(model_, position);  
  return *this;
}

Object& Object::Rotate(float radians, glm::vec3 axes) {
  model_ = glm::rotate(model_, radians, axes);
  return *this;
}

void Object::Draw() const {
  ModelDraw(model_);
}

}  // namespace base
}  // namespace object
}  // namespace fsc