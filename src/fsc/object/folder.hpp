#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <string>

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "complex.hpp"

namespace fsc {
namespace object {

// The Folder class
class Folder final : public Complex {
 public:
  // Constructor
  Folder(std::string path, ObjectData object_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Folder();

  // Refreshes the folder
  void Refresh();

 private:
  // Copy Constructor
  Folder(const Folder&) = delete;

  // Move Constructor
  Folder(Folder &&) = delete;

  // Copy-Assign Constructor
  Folder& operator=(const Folder&) = delete;

  // Move-Assign Constructr
  Folder& operator=(Folder &&) = delete;

 private:
  // The path of the directory
  std::string path_;

  // The size of the directory
  unsigned int size_;

  // The label object
  std::shared_ptr<Object> label_;

  // The plane object
  std::shared_ptr<Object> plane_;
};

}  // namespace object
}  // namespace fsc