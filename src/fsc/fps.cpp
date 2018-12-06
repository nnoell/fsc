//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "fps.hpp"

namespace fsc {

Fps::Fps() :
    base_time_(glfwGetTime()),
    time_diff_(0.1),
    frame_counter_(0),
    fps_(0.0) {
}

Fps::~Fps() {
}

void Fps::Update() {
  // Get the current time, time diff and increase the frame counter
  const double current_time = glfwGetTime();
  time_diff_ = current_time - base_time_;
  frame_counter_++;

  // Update the FPS
  fps_ = frame_counter_ / time_diff_;

  // Check if we have to reset the frame counter and base time
  if (time_diff_ > 1.0) {
    frame_counter_ = 0;
    base_time_ = current_time;
  }
}

double Fps::GetFps() const {
  return fps_;
}

double Fps::GetMillisecondPerFrame() const {
  return 1000.0 / fps_;
}

}  // namespace fsc