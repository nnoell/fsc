#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <filesystem>

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "base/complex.hpp"
#include "base/polygon.hpp"
#include "base/ascii.hpp"

namespace fsc {
namespace object {

// The File class
class File final : public base::Complex {
 public:
  // Constructor
  File(std::filesystem::directory_entry entry,
      base::transformer::Translate translate = {}, base::transformer::Scale scale = {}, base::transformer::Rotate rotate = {}, base::transformer::Model model = {});

  // Destructor
  virtual ~File();

  // Gets the path
  std::filesystem::path GetPath() const;

  // Gets the name
  std::string GetName() const;

  // Checks whether the file is a folder or not
  bool IsFolder() const;

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
  // The directory entry
  const std::filesystem::directory_entry entry_;

  // The base object
  std::shared_ptr<base::Polygon> base_;

  // The cube object
  std::shared_ptr<base::Polygon> cube_;
};

}  // namespace object
}  // namespace fsc