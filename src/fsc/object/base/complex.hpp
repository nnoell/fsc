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
namespace base {

// The Complex class
class Complex : public Object {
 public:
  // Destructor
  virtual ~Complex();

  // Gets the max vertex
  glm::vec3 GetVertexMax() const override;

  // Gets the min vertex
  glm::vec3 GetVertexMin() const override;

  // Draws the complex object
  void Draw() const override;

  // Re-calculates the model matrix
  void RefreshModel() override;

 protected:
  // Constructor
  Complex(transformer::Translate translate = {}, transformer::Scale scale = {}, transformer::Rotate rotate = {}, transformer::Model model = {});

  // Adds a object
  void AddObject(std::shared_ptr<Object> object);

  // Removes a object
  void RemoveObject(unsigned int id);

  // Finds the nested object by Id
  std::shared_ptr<Object> FindObject(unsigned int id) const;

  // Clear Objects
  void ClearObjects();

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
  // The model matrix
  glm::mat4 model_;

  // The list of objects
  std::vector<std::shared_ptr<Object>> objects_;
};

}  // namespace base
}  // namespace object
}  // namespace fsc