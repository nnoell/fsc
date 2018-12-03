#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <string>
#include <array>

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "complex.hpp"
#include "ascii.hpp"
#include "plane.hpp"
#include "cursor.hpp"
#include "file.hpp"

namespace fsc {
namespace object {

// The Folder class
class Folder final : public Complex {
 public:
  // Constructor
  Folder(std::string path, std::shared_ptr<const Folder> parent, ObjectData object_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Folder();

  // Scans the folder for files
  void Scan();

  // Gets the number of files the folder has
  unsigned int GetNumFiles() const;

  // Gets the selected file or null if the folder is empty
  std::shared_ptr<File> GetSelectedFile() const;

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
  const std::string path_;

  // The parent folder
  const std::shared_ptr<const Folder> parent_;

  // The files the folder has
  std::shared_ptr<std::shared_ptr<File> []> files_;

  // The number of files the directory has
  unsigned int num_files_;

  // The number of rows of the folder
  unsigned int num_rows_;

  // The cursor position
  glm::uvec2 cursor_position_;
};

}  // namespace object
}  // namespace fsc