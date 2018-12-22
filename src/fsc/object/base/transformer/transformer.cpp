//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "transformer.hpp"

namespace fsc {
namespace object {
namespace base {
namespace transformer {

Transformer::Transformer(std::string name) :
    name_(std::move(name)) {
}

Transformer::~Transformer() {
}

Transformer::Transformer(const Transformer& other) :
  name_(other.name_) {
}

Transformer::Transformer(Transformer && other) :
  name_(std::move(other.name_)) {
}

Transformer& Transformer::operator=(const Transformer& other) {
  name_ = other.name_;
  return *this;
}

Transformer& Transformer::operator=(Transformer && other) {
  name_ = std::move(other.name_);
  return *this;
}

std::string Transformer::GetName() const {
  return name_;
}

}  // namespace transformer
}  // namespace base
}  // namespace object
}  // namespace fsc