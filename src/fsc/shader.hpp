#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <fstream>
#include <sstream>
#include <iostream>

// PUBLIC
#include <fsc/external.hpp>

namespace fsc {

// The Shader class
class Shader final {
 public:
  // Constructor
  Shader(const char *source_path, GLenum type);

  // Destructor
  virtual ~Shader();

  // Gets the Id
  int GetId() const;

 private:
  // Copy Constructor
  Shader(const Shader&) = delete;

  // Move Constructor
  Shader(Shader &&) = delete;

  // Copy-Assign Constructor
  Shader& operator=(const Shader&) = delete;

  // Move-Assign Constructr
  Shader& operator=(Shader &&) = delete;

 private:
  // The Id
  int id_;
};

}  // namespace fsc