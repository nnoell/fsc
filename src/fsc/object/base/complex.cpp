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
namespace base {

Complex::Complex(std::vector<std::shared_ptr<Object>> objects, ObjectData object_data, glm::mat4 model) :
    Object(std::move(object_data), std::move(model)),
    objects_(std::move(objects)) {
}

Complex::~Complex() {
}

const bool Complex::IsComplex() const {
  return true;
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

void Complex::ClearObjects() {
  objects_.clear();
}

void Complex::ModelDraw(glm::mat4 model) const {
  // Get the object data
  const ObjectData& object_data = GetObjectData();

  // Transform the object model using the object data
  model = glm::scale(model, object_data.scale);
  model = glm::rotate(model, object_data.radians, object_data.axes);
  model = glm::translate(model, object_data.position);

  // Transform each sub-object model using each sub-object model
  for (auto&& object : objects_) {
    if (object->IsComplex()) {
      object->ModelDraw(model);
    } else {
      glm::mat4 model_local = glm::scale(model, object->GetObjectData().scale);
      model_local = glm::rotate(model_local, object->GetObjectData().radians, object->GetObjectData().axes);
      model_local = glm::translate(model_local, object->GetObjectData().position);
      object->ModelDraw(model_local);
    }
  } 
}

}  // namespace base
}  // namespace object
}  // namespace fsc