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
namespace folder {

Details::Details(std::shared_ptr<File> selected_file, unsigned int num_files, std::string path, glm::vec4 color, base::TransformData transform_data , glm::mat4 model) :
    Complex({}, std::move(transform_data), std::move(model)),
    selected_file_(std::move(selected_file)),
    num_files_(std::move(num_files)),
    path_(std::move(path)),
    selected_file_section_(std::make_shared<base::Ascii>("", color, base::TransformData {{-1.5f, -3.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}})),
    num_files_section_(std::make_shared<base::Ascii>("", color, base::TransformData {{-1.5f, -4.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}})),
    path_section_(std::make_shared<base::Ascii>("", color, base::TransformData {{-1.5f, -6.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}})) {
  // Add the objects
  AddObject(selected_file_section_);
  AddObject(num_files_section_);
  AddObject(path_section_);

  // Update the objects
  UpdateSelectedFile();
  UpdateNumFiles();
  UpdatePath();
}

Details::~Details() {
}

void Details::SetSelectedFile(std::shared_ptr<File> selected_file) {
  selected_file_ = std::move(selected_file);
  UpdateSelectedFile();
}

void Details::SetNumFiles(unsigned int num_files) {
  num_files_ = std::move(num_files);
  UpdateNumFiles();
}
  
void Details::SetPath(std::string path) {
  path_ = std::move(path);
  UpdatePath();
}

void Details::UpdateSelectedFile() {
  selected_file_section_->SetAscii("Selected File: " + (selected_file_ ? selected_file_->GetName() : "(NULL)"));
}

void Details::UpdateNumFiles() {
  num_files_section_->SetAscii("Total Files: " + std::to_string(num_files_));
}

void Details::UpdatePath() {
  path_section_->SetAscii("Path: " + path_);
}

Cursor::Cursor(base::TransformData transform_data, glm::mat4 model) :
    Complex(
      {
        std::make_shared<base::Polygon>(base::vertices::GetCube(), glm::vec4 {1.0f, 0.0f, 0.0f, 1.0f}, true, base::TransformData {{0.0f, 0.0f, 0.0f}, {1.5f, 1.5f, 1.5f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}})
      },
      std::move(transform_data),
      std::move(model)) {
}

Cursor::~Cursor() {
}

}  // namespace folder

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

Folder::Folder(std::string path, std::shared_ptr<const Folder> parent, base::TransformData transform_data, glm::mat4 model) :
    Complex({}, std::move(transform_data), std::move(model)),
    path_(std::move(path)),
    parent_(std::move(parent)),
    folder_details_(std::make_shared<folder::Details>(nullptr, 0, path_)),
    cursor_(nullptr),
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
    auto file = std::make_shared<File>(filename, dir_entry.is_directory(), base::TransformData {{x * 5.0f,  2.0f, z * -5.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}});
    files_[x + (z * num_rows_)] = file;
    AddObject(file);

    x++;
  }

  // Add the cursor if the folder is not empty
  if (num_files_ > 0) {
    cursor_ = std::make_shared<folder::Cursor>(base::TransformData {files_[0]->GetPosition() + glm::vec3 {0.0f, 2.0f, 0.0f}, {1.0f, 1.0f, 1.0}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}});
    AddObject(cursor_);
    cursor_position_ = {0, 0};
  }

  // Set and Add the folder details
  folder_details_->SetSelectedFile(GetSelectedFile());
  folder_details_->SetNumFiles(num_files_);
  folder_details_->SetPath(path_);
  AddObject(folder_details_);

  // Create and add the plane
  auto plane = std::make_shared<Plane>(num_rows_, num_rows_, 1, base::TransformData {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}});
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

void Folder::MoveCursorUp() {
  // Check for the new position
  const int new_y = cursor_position_.y + 1;
  if (new_y < 0 || new_y >= num_rows_)
    return;
  const int pos = cursor_position_.x + (new_y * num_rows_);
  if (pos < 0 || pos >= num_files_)
    return;

  // Update the cursor
  cursor_position_.y++;
  UpdateCursor();
}

void Folder::MoveCursorDown() {
  // Check for the new position
  const int new_y = cursor_position_.y - 1;
  if (new_y < 0 || new_y >= num_rows_)
    return;
  const int pos = cursor_position_.x + (new_y * num_rows_);
  if (pos < 0 || pos >= num_files_)
    return;

  // Update the cursor
  cursor_position_.y--;
  UpdateCursor();
}

void Folder::MoveCursorLeft() {
  // Check for the new position
  const int new_x = cursor_position_.x - 1;
  if (new_x < 0 || new_x >= num_rows_)
    return;
  const int pos = new_x + (cursor_position_.y * num_rows_);
  if (pos < 0 || pos >= num_files_)
    return;

  // Update the cursor
  cursor_position_.x--;
  UpdateCursor();
}

void Folder::MoveCursorRight() {
  // Check for the new position
  const int new_x = cursor_position_.x + 1;
  if (new_x < 0 || new_x >= num_rows_)
    return;
  const int pos = new_x + (cursor_position_.y * num_rows_);
  if (pos < 0 || pos >= num_files_)
    return;

  // Update the cursor
  cursor_position_.x++;
  UpdateCursor();
}

void Folder::UpdateCursor() {
  std::shared_ptr<File> selected_file = GetSelectedFile();
  cursor_->SetTransformData({selected_file->GetTransformData().position, {1.0f, 1.0f, 1.0}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}});
  folder_details_->SetSelectedFile(std::move(selected_file));
}

}  // namespace object
}  // namespace fsc