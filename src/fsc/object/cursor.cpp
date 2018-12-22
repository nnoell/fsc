//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "cursor.hpp"
#include "base/vertices/pyramid.hpp"

namespace fsc {
namespace object {

Cursor::Cursor(std::string text, base::transformer::Translate translate, base::transformer::Scale scale, base::transformer::Rotate rotate, base::transformer::Model model) :
    Complex(std::move(translate), std::move(scale), std::move(rotate), std::move(model)),
      pointer_(std::make_shared<base::Polygon>(base::vertices::GetPyramid(), glm::vec4 {1.0f, 0.5f, 0.2f, 1.0f}, false, base::transformer::Translate {{0.0f, -1.0f, 0.0f}}, base::transformer::Scale {{1.5f, 1.5f, 1.5f}}, base::transformer::Rotate {180.0f, {0.0f, 0.0f, 1.0f}})),
      text_(std::make_shared<base::Ascii>(std::move(text), glm::vec4 {1.0f, 0.5f, 0.2f, 1.0f}, base::transformer::Translate {{0.0f, 4.0f, 0.0f}})) {
  // Add the objects
  AddObject(pointer_);
  AddObject(text_);
}

Cursor::~Cursor() {
}

std::string Cursor::GetText() const {
  return text_->GetAscii();
}

void Cursor::SetText(std::string text) {
  text_->SetAscii(std::move(text));
}

}  // namespace object
}  // namespace fsc