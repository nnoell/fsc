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
#include "base/ascii.hpp"
#include "base/polygon.hpp"
#include "plane.hpp"
#include "file.hpp"

namespace fsc {
namespace object {

// The Folder class
class Folder final : public base::Complex {
 public:
  // Constructor
  Folder(std::filesystem::path path, base::TransformData transform_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}});

  // Destructor
  virtual ~Folder();

  // Updates the folder
  void Update();

  // Gets the number of files the folder has
  unsigned int GetNumFiles() const;

  // Gets the number of columns the folder has
  unsigned int GetNumCols() const;

  // Checks if the folder contains a given file id
  bool ContainsFile(unsigned int file_id) const;

  // Gets a file given the row and column of the grid
  std::shared_ptr<File> GetFile(unsigned int row, unsigned int col);

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
  const std::filesystem::path path_;

  // The files the folder has
  std::shared_ptr<std::shared_ptr<File> []> files_;

  // The number of files the directory has
  unsigned int num_files_;

  // The number of cols of the folder
  unsigned int num_cols_;
};

}  // namespace object
}  // namespace fsc