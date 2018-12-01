#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// PUBLIC
#include <fsc/external.hpp>

namespace fsc {

// The Camera class
class Camera final {
 public:
  // Constructor
  Camera();

  // Destructor
  virtual ~Camera();

  // Moves front
  void MoveFront();

  // Moves back
  void MoveBack();

  // Moves left
  void MoveLeft();

  // Moves right
  void MoveRight();

  // Moves up
  void MoveUp();

  // Moves down
  void MoveDown();

  // Looks Up
  void LookUp();

  // Looks down
  void LookDown();

  // Looks left
  void LookLeft();

  // Looks right
  void LookRight();

  // Sets the position
  void SetPosition(glm::vec3 position = {0.0f, 2.0f, 3.0});

  // Sets the front
  void SetFront(glm::vec3 front = {0.0f, 0.0f, -1.0f});

  // Updates the camera changes
  void Update() const;

 private:
  // Updates the camera front
  void UpdateLook();

 private:
  // Copy Constructor
  Camera(const Camera&) = delete;

  // Move Constructor
  Camera(Camera &&) = delete;

  // Copy-Assign Constructor
  Camera& operator=(const Camera&) = delete;

  // Move-Assign Constructr
  Camera& operator=(Camera &&) = delete;

 private:
  // Camera position
  glm::vec3 camera_position_;

  // Camera front
  glm::vec3 camera_front_;

  // Camera up
  glm::vec3 camera_up_;

  // X Euler angle
  float x_euler_angle_;

  // Y Euler angle
  float y_euler_angle_;
};

}  // namespace fsc