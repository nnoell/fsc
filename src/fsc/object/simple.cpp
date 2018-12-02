//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "simple.hpp"

namespace fsc {
namespace object {

Simple::Simple(glm::vec4 color, ObjectData object_data, glm::mat4 model) :
    Object(false, std::move(object_data), std::move(model)),
    color_(std::move(color)) {
}

Simple::~Simple() {
}

glm::vec4 Simple::GetColor() const {
  return color_;
}

}  // namespace object
}  // namespace fsc