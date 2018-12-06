#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <vector>
#include <filesystem>

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "folder.hpp"

namespace fsc {
namespace object {

// The Node class
class Node final : public base::Complex {
 public:
  // Constructor
  Node(std::filesystem::path path, std::shared_ptr<Node> parent, base::TransformData transform_data = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 model = {});

  // Destructor
  virtual ~Node();

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
  // The folder
  std::shared_ptr<Folder> folder_;

  // The parent node
  std::shared_ptr<Node> parent_;

  // The children nodes
  std::vector<std::shared_ptr<Node> > children_;
};

}  // namespace object
}  // namespace fsc