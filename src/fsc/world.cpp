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
    title_("F S C", glm::vec4 {0.0f, 1.0f, 1.0f, 1.0f}, object::base::TransformData {{0.0f, -2.0f, 0.0f}, {7.0f, 7.0f, 7.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}}),
    root_(std::make_shared<object::Node>("C:/", nullptr)),
    selected_node_(root_),
    room_dimension_({0.0f, 0.0f, 30.0f, 30.0f}) {
  // Configure opengl to remeber depth
  glEnable(GL_DEPTH_TEST);

  // Add the root node to the map
  AddNode(root_);
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

  // Draw all the filesystem tree
  root_->Draw();
}

void World::SelectUp() {
  selected_node_->GetFolder()->MoveCursorUp();
}
  
void World::SelectDown() {
  selected_node_->GetFolder()->MoveCursorDown();
}
 
void World::SelectLeft() {
  selected_node_->GetFolder()->MoveCursorLeft();
}

void World::SelectRight() {
  selected_node_->GetFolder()->MoveCursorRight();
}

void World::OpenSelected() {
  // Create the new node
  const auto node = selected_node_->OpenSelectedFolder();
  if (!node)
    return;

  // Add the node
  AddNode(node);

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
  if (node_map_.find(key) == node_map_.end())
    node_map_[key] = {};
  node_map_[key].push_back(std::move(node));
}

void World::UpdateNodePosition() {
  unsigned int key = 0;
  auto it = node_map_.find(key);
  while (it != node_map_.end()) {
    unsigned int i = 0;
    for (auto&& n : it->second) {
      n->SetTransformData({{i * 50.0f, 0.0f, key * -50.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}});
      ++i;
    }
    ++key;
    it = node_map_.find(key);
  }
}

}  // namespace fsc