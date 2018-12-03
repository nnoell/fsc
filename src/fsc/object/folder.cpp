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

namespace fsc {
namespace object {

// Counts the number of files a folder has
static unsigned int CountNumFiles(std::string path) {
  unsigned int res = 0;
  std::filesystem::directory_iterator dir {path};
  for (const std::filesystem::directory_entry& dir_entry : dir)
    ++res;
  return res;
}

// Counts the number of rows the folder has based on the number of files
static unsigned int CountNumRows(unsigned int size) {
  unsigned int res = 0;
  while (res * res < size)
    ++res;
  return res;
}

// The FolderDetals class
class FolderDetails : public Complex {
 public:
  // Constructor
  FolderDetails(std::string path, unsigned int num_files, std::shared_ptr<File> file = nullptr,
      glm::vec4 color = {0.5, 1.0f, 0.0f, 1.0f}, ObjectData object_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {}) :
      Complex(
      {
        std::make_shared<Ascii>("Selected File: " + (file ? file->GetName() : "(NULL)"), color, ObjectData {{-1.5f, -3.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}}),
        std::make_shared<Ascii>("Total Files: " + std::to_string(num_files), color, ObjectData {{-1.5f, -4.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}}),
        std::make_shared<Ascii>("Path: " + path, color, ObjectData {{-1.5f, -6.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}})
      },
      std::move(object_data),
      std::move(model)) {
  }

  // Destructor
  virtual ~FolderDetails() {
  }

 private:
  // Copy Constructor
  FolderDetails(const FolderDetails&) = delete;

  // Move Constructor
  FolderDetails(FolderDetails &&) = delete;

  // Copy-Assign Constructor
  FolderDetails& operator=(const FolderDetails&) = delete;

  // Move-Assign Constructr
  FolderDetails& operator=(FolderDetails &&) = delete;
};

Folder::Folder(std::string path, std::shared_ptr<const Folder> parent, ObjectData object_data, glm::mat4 model) :
    Complex({}, std::move(object_data), std::move(model)),
    path_(path),
    parent_(std::move(parent)),
    files_(nullptr),
    num_files_(0),
    num_rows_(0),
    cursor_position_({0, 0}) {
  // Scan for files
  Scan();
}

Folder::~Folder() {
}

void Folder::Scan() {
  // Clear
  ClearObjects();
  files_ = nullptr;
  num_files_ = 0;
  num_rows_ = 0;
  cursor_position_ = {0, 0};

  // Get the number of files
  num_files_ = CountNumFiles(path_);

  // Get the number of rows
  num_rows_ = CountNumRows(num_files_);

  // Allocate the files array
  files_ = std::shared_ptr<std::shared_ptr<File> []>(new std::shared_ptr<File> [num_files_], std::default_delete<std::shared_ptr<File> []>());

  // Scan and add the files
  unsigned int x = 0;
  unsigned int z = 0;
  std::filesystem::directory_iterator dir {path_};
  for (const std::filesystem::directory_entry& dir_entry : dir) {
    if (x >= num_rows_) {
      x = 0;
      z++;
    }

    // Create the file object and add it into the lists
    const std::string filename = dir_entry.path().filename().string();
    auto file = std::make_shared<File>(filename, dir_entry.is_directory(), ObjectData {{x * 5.0f,  2.0f, z * -5.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}});
    files_[x + (z * num_rows_)] = file;
    AddObject(file);

    x++;
  }

  // Add the curso if the folder is not empty
  if (num_files_ > 0) {
    auto cursor = std::make_shared<Cursor>(object::ObjectData {files_[0]->GetPosition() + glm::vec3 {0.0f, 2.0f, 0.0f}, {1.0f, 1.0f, 1.0}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}});
    AddObject(std::move(cursor));
    cursor_position_ = {0, 0};
  }

  // Create and add the label
  auto label = std::make_shared<FolderDetails>(path_, num_files_, GetSelectedFile());
  AddObject(std::move(label));

  // Create and add the plane
  auto plane = std::make_shared<Plane>(num_rows_, num_rows_, 1, object::ObjectData {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}});
  AddObject(std::move(plane));
}

unsigned int Folder::GetNumFiles() const {
  return num_files_;
}

std::shared_ptr<File> Folder::GetSelectedFile() const {
  if (num_files_ <= 0)
    return nullptr;

  return files_[cursor_position_.x + (cursor_position_.y * num_rows_)];
}

}  // namespace object
}  // namespace fsc