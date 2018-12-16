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

Complex::Complex(transformer::Translate translate, transformer::Scale scale, transformer::Rotate rotate, transformer::Model model) :
    Object(std::move(translate), std::move(scale), std::move(rotate), std::move(model)),
    model_(),
    objects_() {
  // Refresh the model matrix
  RefreshModel();
}

Complex::~Complex() {
}

glm::vec3 Complex::GetVertexMax() const {
  if (objects_.empty())
    return {0.0f, 0.0f, 0.0f};

  // Set max using the first object
  glm::vec3 max = objects_[0]->GetVertexMax();

  // Compare it with the rest of objects
  std::vector<std::shared_ptr<Object>>::const_iterator it;
  for (it = std::next(objects_.begin()); it != objects_.end(); ++it) {
    const auto& object = *it;
    max = glm::max(max, object->GetVertexMax());
  }

  return max;
}

glm::vec3 Complex::GetVertexMin() const {
  if (objects_.empty())
    return {0.0f, 0.0f, 0.0f};

  // Set min using the first object
  glm::vec3 min = objects_[0]->GetVertexMin();

  // Compare it with the rest of objects
  std::vector<std::shared_ptr<Object>>::const_iterator it;
  for (it = std::next(objects_.begin()); it != objects_.end(); ++it) {
    const auto& object = *it;
    min = glm::min(min, object->GetVertexMin());
  }

  return min;
}

void Complex::Draw() const {
  for (auto&& object : objects_)
    object->Draw();
}

void Complex::AddObject(std::shared_ptr<Object> object) {
  // Update the object model
  object->Model({model_});

  // Add it to the list
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

void Complex::RefreshModel() {
  // First we re-calculate the master model
  const glm::mat4 modeled = GetTransformerModel().Transform({});
  const glm::mat4 rotated = GetTransformerRotate().Transform(modeled);
  const glm::mat4 scaled = GetTransformerScale().Transform(rotated);
  model_ = GetTransformerTranslate().Transform(scaled);

  // Then re-calculate the children's model
  for (auto&& object : objects_)
    object->Model({model_});
}

}  // namespace base
}  // namespace object
}  // namespace fsc