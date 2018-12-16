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

  // Gets the model
  const glm::mat4 GetModel() const;

  // Gets the color
  glm::vec4 GetColor() const;

  // Sets the color
  void SetColor(glm::vec4 color);

  // Gets the max vertex
  glm::vec3 GetVertexMax() const override;

  // Gets the min vertex
  glm::vec3 GetVertexMin() const override;

  // Draws the line
  virtual void Draw() const override = 0;

  // Re-calculates the model matrix
  void RefreshModel() override;

 protected:
  // Constructor
  Simple(glm::vec4 color, transformer::Translate translate = {}, transformer::Scale scale = {}, transformer::Rotate rotate = {}, transformer::Model model = {});

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
  // The model matrix
  glm::mat4 model_;

  // The color of the line
  glm::vec4 color_;
};

}  // namespace base
}  // namespace object
}  // namespace fsc