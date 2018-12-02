//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <memory>

// FSC
#include "cursor.hpp"
#include "polygon.hpp"
#include "vertices/pyramid.hpp"
#include "vertices/cube.hpp"

namespace fsc {
namespace object {

Cursor::Cursor(ObjectData object_data, glm::mat4 model) :
    Complex(
      {
        std::make_shared<Polygon>(vertices::GetCube(), glm::vec4 {1.0f, 0.0f, 0.0f, 1.0f}, true, ObjectData {{0.0f, 0.0f, 0.0f}, {1.5f, 1.5f, 1.5f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}})
      },
      std::move(object_data),
      std::move(model)) {
}

Cursor::~Cursor() {
}

}  // namespace object
}  // namespace fsc