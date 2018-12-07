#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "object/base/ascii.hpp"
#include "object/node.hpp"

namespace fsc {

// The World class
class World final {
 public:
  // Constructor
  World(int width, int height, glm::vec4 color);

  // Destructor
  virtual ~World();

  // Update the world changes
  void Update() const;

  // Selects up
  void SelectUp();

  // Selects down
  void SelectDown();

  // Selects Left
  void SelectLeft();

  // Selects Right
  void SelectRight();

  // Opens selected file
  void OpenSelected();

  // Selects the parent node
  void SelectParent();

 private:
  // Copy Constructor
  World(const World&) = delete;

  // Move Constructor
  World(World &&) = delete;

  // Copy-Assign Constructor
  World& operator=(const World&) = delete;

  // Move-Assign Constructr
  World& operator=(World &&) = delete;

 private:
  // The color
  glm::vec4 color_;

  // The projection matrix
  glm::mat4 projection_;

  // The title object
  object::base::Ascii title_;

  // The root node of the filesystem
  std::shared_ptr<object::Node> root_;

  // The selected node
  std::shared_ptr<object::Node> selected_node_;
};

}  // namespace fsc