//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "camera.hpp"
#include "pipeline.hpp"

// The speed of the camera
#define CAMERA_MOVE_SPEED 0.30f
#define CAMERA_TURN_SPEED 0.50f

namespace fsc {

Camera::Camera() :
    camera_position_({0.0f, 2.0f, 3.0f}),
    camera_front_({0.0f, 0.0f, -1.0f}),
    camera_up_({0.0f, 1.0f,  0.0f}),
    x_euler_angle_(0.0f),
    y_euler_angle_(-90.0f) {
    
}

Camera::~Camera() {
}

void Camera::MoveFront() {
  camera_position_ += CAMERA_MOVE_SPEED * camera_front_;
}

void Camera::MoveBack() {
  camera_position_ -= CAMERA_MOVE_SPEED * camera_front_;
}

void Camera::MoveLeft() {
  camera_position_ -= CAMERA_MOVE_SPEED * glm::normalize(glm::cross(camera_front_, camera_up_));
}

void Camera::MoveRight() {
  camera_position_ += CAMERA_MOVE_SPEED * glm::normalize(glm::cross(camera_front_, camera_up_));
}

void Camera::MoveUp() {
  camera_position_ += CAMERA_MOVE_SPEED * camera_up_;
}
 
void Camera::MoveDown() {
  camera_position_ -= CAMERA_MOVE_SPEED * camera_up_;
}

void Camera::LookUp() {
  x_euler_angle_ += CAMERA_TURN_SPEED;
  UpdateLook();
}

void Camera::LookDown() {
  x_euler_angle_ -= CAMERA_TURN_SPEED;
  UpdateLook();
}

void Camera::LookLeft() {
  y_euler_angle_ -= CAMERA_TURN_SPEED;
  UpdateLook();
}

void Camera::LookRight() {
  y_euler_angle_ += CAMERA_TURN_SPEED;
  UpdateLook();
}

void Camera::Update() const {
  // Set the pipeline
  Pipeline::GetInstance().SetMat4("view_", glm::lookAt(camera_position_, camera_position_ + camera_front_, camera_up_));
}

void Camera::UpdateLook() {
  // Make sure X Euler angle is within a valid range
  if (x_euler_angle_ > 89.0f)
    x_euler_angle_ = 89.0f;
  if (x_euler_angle_ < -89.0f)
    x_euler_angle_ = -89.0f;

  camera_front_ = glm::normalize(glm::vec3 {
    cos(glm::radians(y_euler_angle_)) * cos(glm::radians(x_euler_angle_)),
    sin(glm::radians(x_euler_angle_)),
    sin(glm::radians(y_euler_angle_)) * cos(glm::radians(x_euler_angle_))
  });
}

}  // namespace fsc