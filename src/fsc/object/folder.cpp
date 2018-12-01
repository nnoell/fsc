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
#include "polygon.hpp"
#include "text.hpp"
#include "file.hpp"
#include "plane.hpp"

namespace fsc {
namespace object {

Folder::Folder(std::string path) :
    Complex(std::make_shared<Plane>(20, 20, 1), {
      // The path of the Folder
      std::make_shared<Text>(path, glm::vec4 {0.5, 1.0f, 0.0f, 1.0f}, glm::mat4 {}, TextFormat {{0.0f, -2.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}})
      // Extra stuff such as size, date, etc...
    }),
    path_(std::move(path)),
    size_(0) {

  // List all the files
  std::filesystem::directory_iterator dir {path_};
  size_ = 0;
  unsigned int x = 0;
  unsigned int z = 0;
  for (const std::filesystem::directory_entry& dir_entry : dir) {
    // Skip hidden files
    const std::string filename = dir_entry.path().filename().string();
    if (filename[0] == '.')
      continue;

    if (x >= 20) {
      x = 0;
      z++;
    }

    std::shared_ptr<Object> object = std::make_shared<File>(filename, dir_entry.is_directory());
    object->Translate({x * 5.0f,  2.0f, z * -5.0f});
    AddObject(std::move(object));
    x++;
    size_++;
  }
}

Folder::~Folder() {
}

}  // namespace object
}  // namespace fsc