//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "node.hpp"

namespace fsc {
namespace object {

Node::Node(std::filesystem::path path, std::shared_ptr<Node> parent, base::TransformData transform_data, glm::mat4 model) :
    Complex({}, std::move(transform_data), std::move(model)),
    folder_(std::make_shared<Folder>(std::move(path), base::TransformData {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}}, glm::mat4 {})),
    parent_(std::move(parent)),
    selected_node_(nullptr),
    opened_nodes_() {
  AddObject(folder_);
}

Node::~Node() {
}

std::shared_ptr<Folder> Node::GetFolder() const {
  return folder_;
}

std::shared_ptr<Node> Node::GetParent() const {
  return parent_;
}

// Opens the selected folder
std::shared_ptr<Node> Node::OpenSelectedFolder() {
  return OpenFolder(folder_->GetSelectedFile());
}

std::shared_ptr<Node> Node::OpenFolder(std::shared_ptr<File> folder) {
  // Check if the file is a folder
  if (!folder || !folder->IsFolder())
    return nullptr;

  // Check if folder is inside this node
  const unsigned int folder_id = folder->GetId();
  if (!folder_->FindObject(folder_id))
    return nullptr;

  // Check if the file is already open
  std::unordered_map<unsigned int, std::shared_ptr<Node>>::const_iterator it = opened_nodes_.find(folder_id);
  if (it != opened_nodes_.end())
    return it->second;

  // Create and add the node to the list
  selected_node_ = std::make_shared<Node>(folder->GetPath(), shared_from_this(), object::base::TransformData {{0.0f, 0.0f, -50.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}}, glm::mat4 {});
  opened_nodes_[folder_id] = selected_node_;
  AddObject(selected_node_);

  return selected_node_;
}

}  // namespace object
}  // namespace fsc