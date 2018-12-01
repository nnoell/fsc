#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// PUBLIC
#include <fsc/external.hpp>

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
};

}  // namespace fsc