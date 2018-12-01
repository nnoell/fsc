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

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "object.hpp"

namespace fsc {
namespace object {

// The Complex class
class Complex : public Object {
 public:
  // Constructor
  Complex(std::vector<std::shared_ptr<Object>> objects = {}, ObjectData object_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Complex();

  // Finds the nested object by Id
  std::shared_ptr<Object> FindObject(unsigned int id) const;

  // Adds a object
  void AddObject(std::shared_ptr<Object> object);

  // Removes a object
  void RemoveObject(unsigned int id);

 protected:
  // Draws the complex object
  void ModelDraw(glm::mat4 model = {}) const override;

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
  // The list of objects
  std::vector<std::shared_ptr<Object>> objects_;
};

}  // namespace object
}  // namespace fsc