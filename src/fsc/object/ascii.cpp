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

// Creates a vector of Characters given an ascii string
static std::vector<std::shared_ptr<Object>> CreateCharacters(std::string ascii, glm::vec4 color) {
  std::vector<std::shared_ptr<Object>> characters;
  float next_pos = 0.0f;
  for (auto&& c : ascii) {
    auto character = std::make_shared<Character>(c, color, ObjectData {{next_pos, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 0.0f}});
    next_pos += character->GetData().next_position;
    characters.push_back(std::move(character));
  }
  return characters;
}

Ascii::Ascii(std::string ascii, glm::vec4 color, ObjectData object_data, glm::mat4 model) :
    Complex(CreateCharacters(ascii, std::move(color)), std::move(object_data), std::move(model)),
    ascii_(std::move(ascii)) {
}

Ascii::~Ascii() {
}

}  // namespace object
}  // namespace fsc