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
    selected_node_(root_) {
  // Configure opengl to remeber depth
  glEnable(GL_DEPTH_TEST);
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
  selected_node_ = selected_node_->OpenSelectedFolder();
}

void World::SelectParent() {
  selected_node_ = selected_node_->GetParent();
}

}  // namespace fsc