//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "world.hpp"
#include "pipeline.hpp"

namespace fsc {

World::World(int width, int height, glm::vec4 color) :
    color_(std::move(color)),
    projection_(glm::perspective(glm::radians(54.0f), (float)width / (float)height, 0.1f, 1000.0f)),
    title_("F S C", glm::vec4 {0.0f, 1.0f, 1.0f, 1.0f}, object::base::transformer::Translate {{0.0f, -2.0f, 0.0f}}, object::base::transformer::Scale {{7.0f, 7.0f, 7.0f}}, object::base::transformer::Rotate {-90.0f, {1.0f, 0.0f, 0.0f}}),
    root_file_(std::filesystem::directory_entry {"C:/"}),
    root_node_(std::make_shared<object::Node>(root_file_, nullptr)),
    selected_node_(root_node_),
    max_dimension_(root_node_->GetDimension()),
    opened_nodes_map_() {
  // Configure opengl to remeber depth
  glEnable(GL_DEPTH_TEST);

  // Add the root node to the map
  AddNode(root_node_);
}

World::~World() {
}

void World::Update() const {
  // Clear the world
  glClearColor(color_.r, color_.g, color_.b, color_.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set the pipeline
  Pipeline::GetInstance().SetMat4("projection_", projection_);

  // Draw the objects
  title_.Draw();

  // Draw all the opened nodes
  unsigned int key = 0;
  auto it = opened_nodes_map_.find(key);
  while (it != opened_nodes_map_.end()) {
    for (auto&& n : it->second)
      n->Draw();
    ++key;
    it = opened_nodes_map_.find(key);
  }
}

void World::SelectUp() {
  selected_node_->MoveCursorUp();
}
  
void World::SelectDown() {
  selected_node_->MoveCursorDown();
}
 
void World::SelectLeft() {
  selected_node_->MoveCursorLeft();
}

void World::SelectRight() {
  selected_node_->MoveCursorRight();
}

void World::OpenSelected() {
  // Create the new node
  const auto node = selected_node_->OpenSelectedFile();
  if (!node)
    return;

  // Check if it is already open
  if (FindNode(node->GetId())) {
    selected_node_ = node;
    return; 
  }

  // Add the node
  AddNode(node);

  // Update the room dimension
  max_dimension_ = glm::max(max_dimension_, node->GetDimension());

  // Update the position of all nodes
  UpdateNodePosition();

  // Select the node
  selected_node_ = node;
}

void World::SelectParent() {
  const auto node = selected_node_->GetParent();
  if (!node)
    return;

  selected_node_ = node;
}

void World::AddNode(std::shared_ptr<object::Node> node) {
  const unsigned int key = node->GetDepth();
  if (opened_nodes_map_.find(key) == opened_nodes_map_.end())
    opened_nodes_map_[key] = {};
  opened_nodes_map_[key].push_back(std::move(node));
}

void World::RemoveNode(std::shared_ptr<object::Node> node) {
  const unsigned int node_id = node->GetId();
  auto&& nodes_ = opened_nodes_map_[node->GetDepth()];
  nodes_.erase(std::remove_if(nodes_.begin(), nodes_.end(),
      [&](const std::shared_ptr<object::Node>& n){
        return n->GetId() == node_id;
      }));
}

std::shared_ptr<object::Node> World::FindNode(unsigned int node_id) const {
  unsigned int key = 0;
  auto it = opened_nodes_map_.find(key);
  while (it != opened_nodes_map_.end()) {
    for (auto&& n : it->second)
      if (n->GetId() == node_id)
        return n;
    ++key;
    it = opened_nodes_map_.find(key);
  }
  return nullptr;
}

void World::UpdateNodePosition() {
  constexpr float gap = 10.0f;
  unsigned int key = 0;
  auto it = opened_nodes_map_.find(key);
  while (it != opened_nodes_map_.end()) {
    unsigned int i = 0;
    for (auto&& n : it->second) {
      n->Translate(glm::vec3 {i * (max_dimension_.x + gap), 0.0f, -1.0f * key * (max_dimension_.z + gap)});
      ++i;
    }
    ++key;
    it = opened_nodes_map_.find(key);
  }
}

}  // namespace fsc