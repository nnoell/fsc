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
namespace base {

// The Simple class
class Simple : public Object {
 public:
  // Destructor
  virtual ~Simple();

  // Checks whether the object is complex or not
  const bool IsComplex() const override;

  // Gets the color
  glm::vec4 GetColor() const;

  // Sets the color
  void SetColor(glm::vec4 color);

  // Gets the max vertex using a specific model
  glm::vec3 GetModelVertexMax(const glm::mat4& model = {}) const override;

  // Gets the min vertex using a specific model
  glm::vec3 GetModelVertexMin(const glm::mat4& model = {}) const override;

  // Draw the line
  virtual void ModelDraw(const glm::mat4& model = {}) const override = 0;

 protected:
  // Constructor
  Simple(glm::vec4 color, TransformData transform_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

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

}  // namespace base
}  // namespace object
}  // namespace fsc