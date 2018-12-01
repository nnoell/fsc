//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <atomic>
#include <algorithm>

// FSC
#include "complex.hpp"

namespace fsc {
namespace object {

Complex::Complex(std::shared_ptr<Object> master_object, std::vector<std::shared_ptr<Object>> objects) :
    Object(),
    master_object_(std::move(master_object)),
    objects_(std::move(objects)) {
  if (!master_object_)
    throw std::runtime_error("Error: Cannot create a complex object without a master object");
}

Complex::~Complex() {
}

glm::vec3 Complex::GetPosition() const {
  return master_object_->GetPosition();
}

Complex& Complex::Reset() {
  master_object_->Reset();
  for (auto&& object : objects_)
    object->Reset();
  return *this;
}

Complex& Complex::Scale(glm::vec3 factor) {
  master_object_->Scale(factor);
  for (auto&& object : objects_)
    object->Scale(factor);
  return *this;
}

Complex& Complex::Translate(glm::vec3 position) {
  master_object_->Translate(position);
  for (auto&& object : objects_)
    object->Translate(position);
  return *this;
}

Complex& Complex::Rotate(float radians, glm::vec3 axes) {
  master_object_->Rotate(radians, axes);
  for (auto&& object : objects_)
    object->Rotate(radians, axes);
  return *this;
}

void Complex::Draw() const {
  master_object_->Draw();
  for (auto&& object : objects_)
    object->Draw();
}

std::shared_ptr<Object> Complex::GetMasterObject(unsigned int id) const {
  return master_object_;
}

std::shared_ptr<Object> Complex::FindObject(unsigned int id) const {
  for (auto&& object : objects_)
    if (object->GetId() == id)
      return object;
  return nullptr;
}

void Complex::AddObject(std::shared_ptr<Object> object) {
  objects_.push_back(std::move(object));
}

void Complex::RemoveObject(unsigned int id) {
  objects_.erase(std::remove_if(objects_.begin(), objects_.end(),
      [&](const std::shared_ptr<Object>& object){
        return object->GetId() == id;
      }));
}

}  // namespace object
}  // namespace fsc