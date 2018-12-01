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

// The Object base class
class Object {
 public:
  // Destructor
  virtual ~Object();

  // Gets the Id
  unsigned int GetId() const;

  // Gets the current position
  virtual glm::vec3 GetPosition() const = 0;

  // Resets the object
  virtual Object& Reset() = 0;

  // Scales the object
  virtual Object& Scale(glm::vec3 factor) = 0;

  // Translates the object
  virtual Object& Translate(glm::vec3 position) = 0;

  // Rotates the object
  virtual Object& Rotate(float radians, glm::vec3 axes) = 0;

  // Draws the vertex
  virtual void Draw() const = 0;

 protected:
  // Constructor
  Object();

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
};

}  // namespace object
}  // namespace fsc