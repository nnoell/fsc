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
namespace folder {

// The folder Details class
class Details : public base::Complex {
 public:
  // Constructor
  Details(std::shared_ptr<File> selected_file, unsigned int num_files, std::string path, glm::vec4 color = {0.2, 0.8f, 0.8f, 1.0f},
      base::TransformData transform_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Details();

  // Sets the selected file
  void SetSelectedFile(std::shared_ptr<File> selected_file);

  // Sets the number of files
  void SetNumFiles(unsigned int num_files);

  // Sets the path
  void SetPath(std::string path);

 private:
  // Updates the selected file section
  void UpdateSelectedFile();

  // Updates the num files section
  void UpdateNumFiles();

  // Updates the path section
  void UpdatePath();

 private:
  // Copy Constructor
  Details(const Details&) = delete;

  // Move Constructor
  Details(Details &&) = delete;

  // Copy-Assign Constructor
  Details& operator=(const Details&) = delete;

  // Move-Assign Constructr
  Details& operator=(Details &&) = delete;

 private:
  // The selected_file
  std::shared_ptr<File> selected_file_;

  // The number of files
  unsigned int num_files_;

  // The path
  std::string path_;

  // The selected file section
  std::shared_ptr<base::Ascii> selected_file_section_;

  // The num files section
  std::shared_ptr<base::Ascii> num_files_section_;

  // The path section
  std::shared_ptr<base::Ascii> path_section_;
};

// The folder Cursor class
class Cursor final : public base::Complex {
 public:
  // Constructor
  Cursor(std::string text, base::TransformData transform_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Cursor();

  // Gets the text
  std::string GetText() const;

  // Sets the text
  void SetText(std::string text);

 private:
  // Copy Constructor
  Cursor(const Cursor&) = delete;

  // Move Constructor
  Cursor(Cursor &&) = delete;

  // Copy-Assign Constructor
  Cursor& operator=(const Cursor&) = delete;

  // Move-Assign Constructr
  Cursor& operator=(Cursor &&) = delete;

 private:
  // The pointer object
  std::shared_ptr<base::Polygon> pointer_;

  // The text object
  std::shared_ptr<base::Ascii> text_;
};

}  // namespace folder

// The Folder class
class Folder final : public base::Complex {
 public:
  // Constructor
  Folder(std::filesystem::path path, base::TransformData transform_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Folder();

  // Updates the folder
  void Update();

  // Gets the number of files the folder has
  unsigned int GetNumFiles() const;

  // Gets the selected file or null if the folder is empty
  std::shared_ptr<File> GetSelectedFile() const;

  // Checks if the folder contains a given file id
  bool ContainsFile(unsigned int file_id) const;

  // Moves the cursor up
  void MoveCursorUp();

  // Moves the cursor down
  void MoveCursorDown();

  // Moves the cursor to the left
  void MoveCursorLeft();

  // Moves the cursor to the right
  void MoveCursorRight();

 private:
  // Update cursor
  void UpdateCursor();

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

  // The folder details
  std::shared_ptr<folder::Details> folder_details_;

  // The cursor
  std::shared_ptr<folder::Cursor> cursor_;

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