#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "object.hpp"

namespace fsc {
namespace object {

// The Simple class
class Simple : public Object {
 public:
  // Destructor
  virtual ~Simple();

  // Gets the color
  glm::vec4 GetColor() const;

  // Draw the line
  virtual void ModelDraw(glm::mat4 model = {}) const override = 0;

 protected:
  // Constructor
  Simple(glm::vec4 color, ObjectData object_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

 private:
  // Copy Constructor
  Simple(const Simple&) = delete;

  // Move Constructor
  Simple(Simple &&) = delete;

  // Copy-Assign Constructor
  Simple& operator=(const Simple&) = delete;

  // Move-Assign Constructr
  Simple& operator=(Simple &&) = delete;

 private:
  // The color of the line
  glm::vec4 color_;
};

}  // namespace object
}  // namespace fsc