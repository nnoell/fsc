//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "vertices/cube.hpp"
#include "file.hpp"
#include "polygon.hpp"
#include "ascii.hpp"

namespace fsc {
namespace object {

File::File(std::string name, bool is_folder, ObjectData object_data, glm::mat4 model) :
    Complex(
      {
        // The cube
        std::make_shared<Polygon>(vertices::GetCube(), is_folder ? glm::vec4 {1.0f, 1.0f, 1.0f, 1.0f} : glm::vec4 {0.0f, 1.0f, 1.0f, 1.0f}, true),
        // The file name label
        std::make_shared<Ascii>(name, glm::vec4 {0.5, 1.0f, 0.0f, 1.0f}, ObjectData {{2.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(90.0f), {0.0f, 0.0f, 1.0f}})
        // Extra stuff such as size, date, etc...
      },
      std::move(object_data),
      std::move(model)
    ),
    name_(std::move(name)),
    is_folder_(is_folder) {
}

File::~File() {
}

std::string File::GetName() const {
  return name_;
}

}  // namespace object
}  // namespace fsc