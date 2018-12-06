#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <string>

// PUBLIC
#include <fsc/external.hpp>

namespace fsc {

// The Fps class
class Fps final {
 public:
  // Constructor
  Fps();

  // Destructor
  virtual ~Fps();

  // Updates the base time and frame counter values
  void Update();

  // Gets the FPS value
  double GetFps() const;

  // Gets the milliseconds per frame value
  double GetMillisecondPerFrame() const;

 private:
  // The base time
  double base_time_;

  // The time difference since last frame
  double time_diff_;

  // The frame counter
  unsigned int frame_counter_;

  // The number of frames per second
  double fps_;
};

}  // namespace fsc