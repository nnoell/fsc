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

// The File class
class File final : public Complex {
 public:
  // Constructor
  File(std::string name, bool is_folder = false);

  // Destructor
  virtual ~File();

 private:
  // Copy Constructor
  File(const File&) = delete;

  // Move Constructor
  File(File &&) = delete;

  // Copy-Assign Constructor
  File& operator=(const File&) = delete;

  // Move-Assign Constructr
  File& operator=(File &&) = delete;

 private:
  // The name of the file
  std::string name_;

  // Whether this file is a folder or not
  bool is_folder_;
};

}  // namespace object
}  // namespace fsc