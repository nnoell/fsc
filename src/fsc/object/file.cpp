//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "vertices/cube.hpp"
#include "file.hpp"
#include "polygon.hpp"

namespace fsc {
namespace object {

File::File(std::string name, bool is_folder) :
    Complex(
      std::make_shared<Polygon>(vertices::GetCube(), is_folder ? glm::vec4 {1.0f, 0.5f, 0.25f, 1.0f} : glm::vec4 {0.0f, 1.0f, 1.0f, 1.0f}, true), {
        // The file name
        std::make_shared<Text>(name, glm::vec4 {0.5, 1.0f, 0.0f, 1.0f}, glm::mat4 {}, TextFormat {{1.5f, -0.4f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(90.0f), {0.0f, 0.0f, 1.0f}})
        // Extra stuff such as size, date, etc...
      }),
    name_(std::move(name)),
    is_folder_(is_folder) {
}

File::~File() {
}

}  // namespace object
}  // namespace fsc