#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <string>

// PUBLIC
#include <fsc/external.hpp>

namespace fsc {
namespace object {
namespace base {

// The transform data type
struct TransformData {
  // The position
  glm::vec3 position;

  // The size
  glm::vec3 scale;

  // The radians
  float radians;

  // The axes
  glm::vec3 axes;
};

// The Object base class
class Object {
 public:
  // Destructor
  virtual ~Object();

  // Gets the Id
  unsigned int GetId() const;

  // Checks whether the object is complex or not
  virtual const bool IsComplex() const = 0;

  // Gets the transform data
  const TransformData& GetTransformData() const;

  // Sets the transform data
  void SetTransformData(TransformData transform_data);

  // Gets the current position
  glm::vec3 GetPosition() const;
  
  // Transforms the object
  glm::mat4 Transform();

  // Transforms the object using a specific model
  glm::mat4 ModelTransform(const glm::mat4& model = {}) const;

  // Draws the object
  void Draw() const;

  // Draws using a specific model
  virtual void ModelDraw(const glm::mat4& model = {}) const = 0;

 protected:
  // Constructor
  Object(TransformData transform_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

 private:
  // Copy Constructor
  Object(const Object&) = delete;

  // Move Constructor
  Object(Object &&) = delete;

  // Copy-Assign Constructor
  Object& operator=(const Object&) = delete;

  // Move-Assign Constructr
  Object& operator=(Object &&) = delete;

 private:
  // The Id
  const unsigned int id_;

  // The transform data
  TransformData transform_data_;

  // The model matrix
  glm::mat4 model_;
};

}  // namespace base
}  // namespace object
}  // namespace fsc