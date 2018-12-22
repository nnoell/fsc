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

Ascii::Ascii(std::string ascii, glm::vec4 color, transformer::Translate translate, transformer::Scale scale, transformer::Rotate rotate, transformer::Model model) :
    Complex(std::move(translate), std::move(scale), std::move(rotate), std::move(model)),
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
    const std::shared_ptr<Character> character = std::make_shared<Character>(c, color_, transformer::Translate {{next_pos, 0.0f, 0.0f}});
    next_pos += character->GetNextPosition();
    AddObject(std::move(character));
  }
}

}  // namespace base
}  // namespace object
}  // namespace fsc