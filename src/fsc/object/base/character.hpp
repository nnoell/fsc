#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "vertices/font.hpp"
#include "simple.hpp"

namespace fsc {
namespace object {
namespace base {

// The Character class
class Character final : public Simple {
 public:
  // Constructor
  Character(char character, glm::vec4 color = glm::vec4 {0.5, 1.0f, 0.0f, 1.0f}, ObjectData object_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Character();

  // Gets the character
  char GetCharacter() const;

  // Sets the character
  void SetCharacter(char character);

  // Gets the data
  const vertices::CharData& GetData() const;

  // Draws the text object
  void ModelDraw(glm::mat4 model = {}) const override;

 private:
  // Copy Constructor
  Character(const Character&) = delete;

  // Move Constructor
  Character(Character &&) = delete;

  // Copy-Assign Constructor
  Character& operator=(const Character&) = delete;

  // Move-Assign Constructr
  Character& operator=(Character &&) = delete;

 private:
  // The character
  char character_;
};

}  // namespace base
}  // namespace object
}  // namespace fsc