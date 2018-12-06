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

Complex::Complex(std::vector<std::shared_ptr<Object>> objects, TransformData transform_data, glm::mat4 model) :
    Object(std::move(transform_data), std::move(model)),
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

void Complex::ModelDraw(const glm::mat4& model) const {
  // Transform the object model using the transform data
  glm::mat4 model2 = ModelTransform(model);

  // Transform each sub-object model using each sub-object model
  for (auto&& object : objects_) {
    if (object->IsComplex())
      object->ModelDraw(model2);
    else
      object->ModelDraw(object->ModelTransform(model2));
  } 
}

}  // namespace base
}  // namespace object
}  // namespace fsc