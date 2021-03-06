#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "vertices/data.hpp"
#include "simple.hpp"

namespace fsc {
namespace object {
namespace base {

// The Character class
class Character final : public Simple {
 public:
  // Constructor
  Character(char character, glm::vec4 color = glm::vec4 {0.5, 1.0f, 0.0f, 1.0f},
      transformer::Translate translate = {}, transformer::Scale scale = {}, transformer::Rotate rotate = {}, transformer::Model model = {});

  // Destructor
  virtual ~Character();

  // Gets the character
  char GetCharacter() const;

  // Sets the character
  void SetCharacter(char character);

  // Gets the next position for the next character
  float GetNextPosition() const;

  // Draws the text object
  void Draw() const override;

 private:
  // Updates the changes
  void Update();

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

  // The vertices data
  std::shared_ptr<const vertices::CharData> vertices_data_;

  // The Vertex Array Object
  unsigned int vao_;

  // The buffer Array Object
  unsigned int vbo_;
};

}  // namespace base
}  // namespace object
}  // namespace fsc