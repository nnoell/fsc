//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "ascii.hpp"
#include "character.hpp"

namespace fsc {
namespace object {
namespace base {

Ascii::Ascii(std::string ascii, glm::vec4 color, TransformData transform_data, glm::mat4 model) :
    Complex(std::move(transform_data), std::move(model)),
    ascii_(std::move(ascii)),
    color_(std::move(color)) {
  // Update the objects
  Update();
}

Ascii::~Ascii() {
}

std::string Ascii::GetAscii() const {
  return ascii_;
}

void Ascii::SetAscii(std::string ascii) {
  ascii_ = ascii;
  Update();
}

void Ascii::Update() {
  // Clears the objects
  ClearObjects();

  // Add the new objects
  float next_pos = 0.0f;
  for (auto&& c : ascii_) {
    auto character = std::make_shared<Character>(c, color_, TransformData {{next_pos, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 0.0f}});
    next_pos += character->GetNextPosition();
    AddObject(std::move(character));
  }
}

}  // namespace base
}  // namespace object
}  // namespace fsc