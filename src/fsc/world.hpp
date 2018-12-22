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
  // Adds a node to the map
  void AddNode(std::shared_ptr<object::Node> node);

  // Removes a node from the map
  void RemoveNode(std::shared_ptr<object::Node> node);

  // Finds a node in the map given it's Id
  std::shared_ptr<object::Node> FindNode(unsigned int file_id) const;

  // Updates the cursor position
  void UpdateCursorPosition();

  // Updates the position of all nodes
  void UpdateNodePosition();

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

  // The cursor
  object::Cursor cursor_;

  // The root file
  const object::File root_file_;

  // The root node
  std::shared_ptr<object::Node> root_node_;

  // The selected node
  std::shared_ptr<object::Node> selected_node_;

  // The max room dimension for each node
  glm::vec3 max_dimension_;

  // The map with all opened nodes
  std::unordered_map<unsigned int, std::vector<std::shared_ptr<object::Node> > > opened_nodes_map_;
};

}  // namespace fsc