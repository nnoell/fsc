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

glm::vec3 Complex::GetModelVertexMiddle(const glm::mat4& model) const {
  glm::vec3 middle = GetModelVertexMax(model) + GetModelVertexMin(model);
  middle /= 2;
  return middle;
}

glm::vec3 Complex::GetModelVertexMax(const glm::mat4& model) const {
  glm::mat4 model2 = ModelTransform(model);

  bool first_object = true;
  glm::vec3 max;
  for (auto&& object : objects_) {
    if (object->IsComplex()) {
      if (first_object)
        max = object->GetModelVertexMax(model2);
      else
        max = glm::max(max, object->GetModelVertexMax(model2));
    } else {
      if (first_object)
        max = object->GetModelVertexMax(object->ModelTransform(model2));
      else
        max = glm::max(max, object->GetModelVertexMax(object->ModelTransform(model2)));
    }
    first_object = false;
  }
  return max;
}

glm::vec3 Complex::GetModelVertexMin(const glm::mat4& model) const {
  glm::mat4 model2 = ModelTransform(model);

  bool first_object = true;
  glm::vec3 min;
  for (auto&& object : objects_) {
    if (object->IsComplex()) {
      if (first_object)
        min = object->GetModelVertexMin(model2);
      else
        min = glm::min(min, object->GetModelVertexMin(model2));
    } else {
      if (first_object)
        min = object->GetModelVertexMin(object->ModelTransform(model2));
      else
        min = glm::min(min, object->GetModelVertexMin(object->ModelTransform(model2)));
    }
    first_object = false;
  }
  return min;
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

void Complex::AddObject(std::shared_ptr<Object> object) {
  objects_.push_back(std::move(object));
}

void Complex::RemoveObject(unsigned int id) {
  objects_.erase(std::remove_if(objects_.begin(), objects_.end(),
      [&](const std::shared_ptr<Object>& object){
        return object->GetId() == id;
      }));
}

std::shared_ptr<Object> Complex::FindObject(unsigned int id) const {
  for (auto&& object : objects_)
    if (object->GetId() == id)
      return object;
  return nullptr;
}

void Complex::ClearObjects() {
  objects_.clear();
}

}  // namespace base
}  // namespace object
}  // namespace fsc