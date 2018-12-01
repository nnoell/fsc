#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <string>

// FSC
#include "../external.hpp"
#include "object.hpp"

namespace fsc {
namespace object {

// The text fortmat type
struct TextFormat {
  // The position
  glm::vec3 position;

  // The size
  glm::vec3 scale;

  // The radians
  float radians;

  // The axes
  glm::vec3 axes;
};

// The Text class
class Text final : public Object {
 public:
  // Constructor
  Text(std::string text, glm::vec4 color, glm::mat4 model = {}, TextFormat format = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}});

  // Destructor
  virtual ~Text();

  // Gets the current position
  glm::vec3 GetPosition() const override;

  // Resets the test object
  Text& Reset() override;

  // Scales the text object
  Text& Scale(glm::vec3 factor) override;

  // Translates the text object
  Text& Translate(glm::vec3 position) override;

  // Rotates the text object
  Text& Rotate(float radians, glm::vec3 axes) override;

  // Draws the text object
  void Draw() const override;

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

  // The matrix model
  glm::mat4 model_;

  // The format
  TextFormat format_;
};

}  // namespace object
}  // namespace fsc