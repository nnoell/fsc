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

// FSC
#include "object.hpp"

namespace fsc {
namespace object {

// The Text class
class Text final : public Object {
 public:
  // Constructor
  Text(std::string text, glm::vec4 color, ObjectData object_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Text();

  // Draws the text object
  void ModelDraw(glm::mat4 model = {}) const override;

 private:
  // Copy Constructor
  Text(const Text&) = delete;

  // Move Constructor
  Text(Text &&) = delete;

  // Copy-Assign Constructor
  Text& operator=(const Text&) = delete;

  // Move-Assign Constructr
  Text& operator=(Text &&) = delete;

 private:
  // The text
  std::string text_;

  // The text color
  glm::vec4 color_;
};

}  // namespace object
}  // namespace fsc