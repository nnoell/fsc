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
#include "base/line.hpp"

namespace fsc {
namespace object {

// The Node class
class Node final : public base::Complex, public std::enable_shared_from_this<Node> {
 public:
  // Constructor
  Node(const File& file, std::shared_ptr<Node> parent, base::TransformData transform_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Node();

  // Gets the folder of the node
  std::shared_ptr<Folder> GetFolder() const;

  // Gets the parent
  std::shared_ptr<Node> GetParent() const;

  // Gets the depth
  unsigned int GetDepth() const;

  // Opens the selected file
  std::shared_ptr<Node> OpenSelectedFile();

  // Opens a file within the node
  std::shared_ptr<Node> OpenFile(const File& file);

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

  // The origin line
  const std::shared_ptr<base::Line> origin_line_;

  // The selected node
  std::shared_ptr<Node> selected_node_;

  // Opened nodes
  std::unordered_map<unsigned int, std::shared_ptr<Node>> opened_nodes_;
};

}  // namespace object
}  // namespace fsc