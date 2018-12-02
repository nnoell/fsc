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

  // Refreshes the folder
  void Refresh();

  // Gets the selected file
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
  std::string path_;

  // The size of the directory
  unsigned int size_;

  // The parent folder
  const std::shared_ptr<const Folder> parent_;

  // Opened folders
  std::vector<std::shared_ptr<Folder> > opened_folders_;

  // The label object
  std::shared_ptr<Ascii> label_;

  // The plane object
  std::shared_ptr<Plane> plane_;

  // The cursor object
  std::shared_ptr<Cursor> cursor_;

  // The selected file
  std::shared_ptr<File> selected_file_;
};

}  // namespace object
}  // namespace fsc