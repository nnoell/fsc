//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <memory>
#include <filesystem>

// FSC
#include "folder.hpp"
#include "ascii.hpp"
#include "file.hpp"
#include "plane.hpp"

namespace fsc {
namespace object {

Folder::Folder(std::string path, ObjectData object_data, glm::mat4 model) :
    Complex({}, std::move(object_data), std::move(model) ),
    path_(path),
    size_(0),
    label_(std::make_shared<Ascii>(path, glm::vec4 {0.5, 1.0f, 0.0f, 1.0f}, ObjectData {{0.0f, -2.5f, 0.0f}, {2.0f, 2.0f, 2.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}})),
    plane_(std::make_shared<Plane>(1, 1, 1, object::ObjectData {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}})) {
  Refresh();
}

Folder::~Folder() {
}

void Folder::Refresh() {
  // Count the number of files the folder has
  {
    size_ = 0;
    std::filesystem::directory_iterator dir {path_};
    for (const std::filesystem::directory_entry& dir_entry : dir)
      ++size_;
  }

  // Get the sqrt of the size
  unsigned int i = 0;
  while (i * i < size_)
    ++i;

  // Clear all the objects
  ClearObjects();

  // Create new plane and add it
  plane_ = std::make_shared<Plane>(i, i, 1, object::ObjectData {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}});
  AddObject(plane_);

  // Add the label
  AddObject(label_);

  // Add the files
  {
    unsigned int x = 0;
    unsigned int z = 0;
    std::filesystem::directory_iterator dir {path_};
    for (const std::filesystem::directory_entry& dir_entry : dir) {
      if (x >= i) {
        x = 0;
        z++;
      }

      const std::string filename = dir_entry.path().filename().string();
      AddObject(std::make_shared<File>(filename, dir_entry.is_directory(), ObjectData {{x * 5.0f,  2.0f, z * -5.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}}));
      x++;
    }
  }
}

}  // namespace object
}  // namespace fsc