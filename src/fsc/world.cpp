//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <iostream>

// FSC
#include "world.hpp"
#include "pipeline.hpp"

namespace fsc {

World::World(int width, int height, glm::vec4 color) :
    color_(std::move(color)),
    projection_(glm::perspective(glm::radians(54.0f), (float)width / (float)height, 0.1f, 1000.0f)),
    title_("F S C", glm::vec4 {0.0f, 1.0f, 1.0f, 1.0f}, object::base::TransformData {{0.0f, -2.0f, 0.0f}, {7.0f, 7.0f, 7.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}}),
    root_(std::make_shared<object::Folder>("C:/", nullptr)),
    opened_folders_({}) {
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

  // Draw the root folder
  root_->Draw();

  // Draw the opened folders
  for (const auto& f : opened_folders_)
    f->Draw();
}

void World::SelectUp() {
  root_->MoveCursorUp();
}
  
void World::SelectDown() {
  root_->MoveCursorDown();
}
 
void World::SelectLeft() {
  root_->MoveCursorLeft();
}

void World::SelectRight() {
  root_->MoveCursorRight();
}

void World::OpenSelected() {
  std::shared_ptr<object::File> file = root_->GetSelectedFile();
  if (!file->IsFolder())
    return;

  std::cout << file->GetPath() << std::endl;
  auto folder = std::make_shared<object::Folder>(file->GetPath(), root_, object::base::TransformData {{0.0f, 0.0f, -50.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}});
  opened_folders_.push_back(std::move(folder));
}

}  // namespace fsc