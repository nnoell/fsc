#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <vector>
#include <memory>
#include <string>

// FSC
#include "../external.hpp"
#include "object.hpp"

namespace fsc {
namespace object {

// The Complex class
class Complex : public Object {
 public:
  // Constructor
  Complex(std::shared_ptr<Object> master_object, std::vector<std::shared_ptr<Object>> objects = {});

  // Destructor
  virtual ~Complex();

  // Gets the current position
  glm::vec3 GetPosition() const override;

  // Resets the complex object
  Complex& Reset() override;

  // Scales the complex object
  Complex& Scale(glm::vec3 factor) override;

  // Translates the complex object
  Complex& Translate(glm::vec3 position) override;

  // Rotates the complex object
  Complex& Rotate(float radians, glm::vec3 axes) override;

  // Draws the complex object
  void Draw() const override;

  // Gets the master object
  std::shared_ptr<Object> GetMasterObject(unsigned int id) const;

  // Finds the nested object by Id
  std::shared_ptr<Object> FindObject(unsigned int id) const;

  // Adds a object
  void AddObject(std::shared_ptr<Object> object);

  // Removes a object
  void RemoveObject(unsigned int id);

 private:
  // Copy Constructor
  Complex(const Complex&) = delete;

  // Move Constructor
  Complex(Complex &&) = delete;

  // Copy-Assign Constructor
  Complex& operator=(const Complex&) = delete;

  // Move-Assign Constructr
  Complex& operator=(Complex &&) = delete;

 private:
  // The id
  unsigned int id_;

  // The master object
  std::shared_ptr<Object> master_object_;

  // The list of objects
  std::vector<std::shared_ptr<Object>> objects_;
};

}  // namespace object
}  // namespace fsc