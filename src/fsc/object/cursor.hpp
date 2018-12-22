#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "base/polygon.hpp"
#include "base/ascii.hpp"

namespace fsc {
namespace object {

// The folder Cursor class
class Cursor final : public base::Complex {
 public:
  // Constructor
  Cursor(std::string text,
      base::transformer::Translate translate = {}, base::transformer::Scale scale = {}, base::transformer::Rotate rotate = {}, base::transformer::Model model = {});

  // Destructor
  virtual ~Cursor();

  // Gets the text
  std::string GetText() const;

  // Sets the text
  void SetText(std::string text);

 private:
  // Copy Constructor
  Cursor(const Cursor&) = delete;

  // Move Constructor
  Cursor(Cursor &&) = delete;

  // Copy-Assign Constructor
  Cursor& operator=(const Cursor&) = delete;

  // Move-Assign Constructr
  Cursor& operator=(Cursor &&) = delete;

 private:
  // The pointer object
  std::shared_ptr<base::Polygon> pointer_;

  // The text object
  std::shared_ptr<base::Ascii> text_;
};

}  // namespace object
}  // namespace fsc