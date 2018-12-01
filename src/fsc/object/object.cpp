//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <atomic>

// FSC
#include "object.hpp"

namespace fsc {
namespace object {

// Gets a unique Id
static unsigned int GetUniqueId() {
  static std::atomic<unsigned int> id(0);
  return id++;
}

Object::Object() :
    id_(GetUniqueId()) {
}

Object::~Object() {
}

unsigned int Object::GetId() const {
  return id_;
}

}  // namespace object
}  // namespace fsc