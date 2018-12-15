//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <memory>
#include <filesystem>

// FSC
#include "base/vertices/pyramid.hpp"
#include "folder.hpp"

namespace fsc {
namespace object {

// Counts the number of files a folder has
static std::vector<std::filesystem::directory_entry> GetDirectoryEntries(std::filesystem::path path) {
  // Access denied might happen when creating a directory iterator
  try {
    std::vector<std::filesystem::directory_entry> entries;
    std::filesystem::directory_iterator dir {path};
    for (const std::filesystem::directory_entry& dir_entry : dir)
      entries.push_back(dir_entry);
    return entries;
  } catch (...) {
    return {};
  }
}

// Counts the number of cols the folder has based on the number of files
static unsigned int CountNumCols(unsigned int size) {
  unsigned int res = 0;
  while (res * res < size)
    ++res;
  return res;
}

Folder::Folder(std::filesystem::path path, base::TransformData transform_data) :
    Complex(std::move(transform_data)),
    path_(std::move(path)),
    files_(nullptr),
    num_files_(0),
    num_cols_(0) {
  // Update the folder
  Update();
}

Folder::~Folder() {
}

void Folder::Update() {
  // Clear
  ClearObjects();
  files_ = nullptr;
  num_files_ = 0;
  num_cols_ = 0;

  // Get the directory entries
  const std::vector<std::filesystem::directory_entry> entries = GetDirectoryEntries(path_);

  // Set the number of files
  num_files_ = entries.size();

  // Set the number of columns
  num_cols_ = CountNumCols(num_files_);

  // Retirn of the folder is empty
  if (num_files_ <= 0)
    return;

  // Allocate the files array
  files_ = std::shared_ptr<std::shared_ptr<File> []>(new std::shared_ptr<File> [num_files_], std::default_delete<std::shared_ptr<File> []>());

  // Create the files and add them
  unsigned int x = 0;
  unsigned int z = 0;
  for (const std::filesystem::directory_entry& entry : entries) {
    if (x >= num_cols_) {
      x = 0;
      z++;
    }

    // Create the file object and add it into the lists
    auto file = std::make_shared<File>(entry, base::TransformData {{x * 5.0f,  0.0f, z * -5.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}});
    files_[x + (z * num_cols_)] = file;
    AddObject(file);

    x++;
  }
}

unsigned int Folder::GetNumFiles() const {
  return num_files_;
}

unsigned int Folder::GetNumCols() const {
  return num_cols_;
}

bool Folder::ContainsFile(unsigned int file_id) const {
  return FindObject(file_id) != nullptr;
}

std::shared_ptr<File> Folder::GetFile(unsigned int row, unsigned int col) {
  if (num_files_ <= 0)
    return nullptr;

  return files_[row + (col * num_cols_)];
}

}  // namespace object
}  // namespace fsc