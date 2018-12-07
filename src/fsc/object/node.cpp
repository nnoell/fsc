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
    folder_(std::make_shared<Folder>(std::move(path), base::TransformData {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0, {1.0f, 1.0f, 1.0f}}, glm::mat4 {})),
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

void Node::OpenSelectedFile() {
  // Get the selected file
  std::shared_ptr<object::File> file = folder_->GetSelectedFile();
  if (!file->IsFolder())
    return;

  // Check if the file is already open
  const unsigned int id = file->GetId();
  std::unordered_map<unsigned int, std::shared_ptr<Node>>::const_iterator it = opened_nodes_.find(id);
  if (it != opened_nodes_.end())
    return;

  // Create and add the node to the list
  selected_node_ = std::make_shared<Node>(file->GetPath(), shared_from_this(), object::base::TransformData {{0.0f, 0.0f, -50.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}}, glm::mat4 {});
  opened_nodes_[id] = selected_node_;
  AddObject(selected_node_);
}

}  // namespace object
}  // namespace fsc