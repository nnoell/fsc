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
    title_("File System Cyberspace", glm::vec4 {0.0f, 1.0f, 1.0f, 1.0f}, object::ObjectData {{0.0f, -3.0f, 0.0f}, {5.0f, 5.0f, 5.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}}),
    root_("C:/Windows", nullptr) {
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

  // Draw the tree
  root_.Draw();
}

}  // namespace fsc