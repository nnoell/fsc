//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "node.hpp"

namespace fsc {
namespace object {

Node::Node(const File& file, std::shared_ptr<Node> parent, base::TransformData transform_data, glm::mat4 model) :
    Complex({}, std::move(transform_data), std::move(model)),
    file_(file),
    folder_(std::make_shared<Folder>(file_.GetPath(), base::TransformData {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}}, glm::mat4 {})),
    parent_(std::move(parent)),
    depth_(!parent_ ? 0 : parent_->GetDepth() + 1),
    origin_line_(std::make_shared<base::Line>(std::vector<glm::vec3>{}, glm::vec4 {1.0f, 0.5f, 0.2f, 1.0f})),
    selected_node_(nullptr),
    opened_nodes_() {
  AddObject(folder_);
  AddObject(origin_line_);
}

Node::~Node() {
}

std::shared_ptr<Folder> Node::GetFolder() const {
  return folder_;
}

std::shared_ptr<Node> Node::GetParent() const {
  return parent_;
}

unsigned int Node::GetDepth() const {
  return depth_;
}

// Opens the selected folder
std::shared_ptr<Node> Node::OpenSelectedFile() {
  std::shared_ptr<File> selected_file = folder_->GetSelectedFile();
  if (!selected_file)
    return nullptr;

  return OpenFile(*selected_file);
}

std::shared_ptr<Node> Node::OpenFile(const File& file) {
  // Check if the file is a folder
  if (!file.IsFolder())
    return nullptr;

  // Check if file is within this node
  const unsigned int folder_id = file.GetId();
  if (!folder_->FindObject(folder_id))
    return nullptr;

  // Check if the file is already open
  std::unordered_map<unsigned int, std::shared_ptr<Node>>::const_iterator it = opened_nodes_.find(folder_id);
  if (it != opened_nodes_.end())
    return it->second;

  // Create and add the node to the list
  selected_node_ = std::make_shared<Node>(file, shared_from_this());
  opened_nodes_[folder_id] = selected_node_;

  return selected_node_;
}

void Node::Update() {
  origin_line_->SetPoints({file_.GetVertexMiddle(), GetVertexMiddle()});
}

}  // namespace object
}  // namespace fsc