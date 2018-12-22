#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <memory>
#include <vector>
#include <unordered_map>
#include <filesystem>

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "folder.hpp"
#include "cursor.hpp"
#include "base/line.hpp"

namespace fsc {
namespace object {
namespace node {

// The node Details class
class Details : public base::Complex {
 public:
  // Constructor
  Details(std::shared_ptr<File> selected_file, unsigned int num_files, std::string path, glm::vec4 color = {0.2, 0.8f, 0.8f, 1.0f},
      base::transformer::Translate translate = {}, base::transformer::Scale scale = {}, base::transformer::Rotate rotate = {}, base::transformer::Model model = {});

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

}  // namespace node

// The Node class
class Node final : public base::Complex {
 public:
  // Constructor
  Node(const File& file, std::shared_ptr<Node> parent,
      base::transformer::Translate translate = {}, base::transformer::Scale scale = {}, base::transformer::Rotate rotate = {}, base::transformer::Model model = {});

  // Destructor
  virtual ~Node();

  // Gets the file this node belongs to
  const File& GetFile() const;

  // Gets the folder
  const std::shared_ptr<Folder> GetFolder() const;

  // Gets the parent
  std::shared_ptr<Node> GetParent() const;

  // Gets the depth
  unsigned int GetDepth() const;

  // Gets the selected file
  std::shared_ptr<File> GetSelectedFile() const;

  // Selects the upper file
  void SelectFileUp();

  // Selects the lower file
  void SelectFileDown();

  // Selects the left file
  void SelectFileLeft();

  // Selected the right file
  void SelectFileRight();

  // Updates the node
  void Update();

 private:
  // Copy Constructor
  Node(const Node&) = delete;

  // Move Constructor
  Node(Node &&) = delete;

  // Copy-Assign Constructor
  Node& operator=(const Node&) = delete;

  // Move-Assign Constructr
  Node& operator=(Node &&) = delete;

 private:
  // The file this node belongs to
  const File& file_;

  // The folder
  std::shared_ptr<Folder> folder_;

  // The parent node
  const std::shared_ptr<Node> parent_;

  // The depth
  const unsigned int depth_;

  // The cursor position
  glm::uvec2 cursor_position_;

  // The origin line
  const std::shared_ptr<base::Line> origin_line_;

  // The node details
  const std::shared_ptr<node::Details> details_;
};

}  // namespace object
}  // namespace fsc