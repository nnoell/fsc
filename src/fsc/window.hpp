#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <memory>
#include <functional>
#include <unordered_map>
#include <mutex>
#include <string>

// PUBLIC
#include <fsc/external.hpp>

namespace fsc {

// The Window class
class Window final {
 public:
  // The Key function type
  using KeyFunction = std::function<void(void)>;

  // The Key function configuration type
  struct KeyFunctionConf {
    // Callback used when the key is pressed
    KeyFunction press_callback;

    // Whether to block the pressed callback until released
    bool block_until_released;

    // Whether the key is blocked or not
    bool is_blocked;
  };

  // The mouse function type
  using MouseFunction = std::function<void(double, double)>;

  // The resize function type
  using ResizeFunction = std::function<void(int, int)>;

  // The render function type
  using RenderFunction = std::function<void(void)>;

 public:
  // Constructor
  Window(unsigned int width, unsigned int height, std::string title);

  // Destructor
  virtual ~Window();

  // Adds a key callback
  void AddKeyCallback(int key, KeyFunction pressed, bool block_until_released = false);

  // Sets the mouse callback
  void SetMouseCallback(MouseFunction callback);

  // Sets the resize callback
  void SetResizeCallback(ResizeFunction callback);

  // Calls the mouse callback
  void CallMouseCallback(double x, double y);

  // Calls the resize callback
  void CallResizeCallback(int w, int h);

  // Renders the window
  void Render(RenderFunction render_function = [](){});

 private:
  // Updates the window title
  void UpdateWindowTitle(double fps, double msframe);

  // Processes the input
  void ProcessInput();

 private:
  // Copy Constructor
  Window(const Window&) = delete;

  // Move Constructor
  Window(Window &&) = delete;

  // Copy-Assign Constructor
  Window& operator=(const Window&) = delete;

  // Move-Assign Constructr
  Window& operator=(Window &&) = delete;

 private:
  // The title
  const std::string title_;

  // The window 
  const std::shared_ptr<GLFWwindow> window_;

  // The key callback map mutex
  mutable std::mutex key_callback_map_mutex_;

  // The mouse callback mutex
  mutable std::mutex mouse_callback_mutex_;

  // The resize callback mutex
  mutable std::mutex resize_callback_mutex_;

  // The key callback map
  std::unordered_map<int, KeyFunctionConf> key_callback_map_;

  // The mouse callback
  MouseFunction mouse_callback_;

  // The resize callback
  ResizeFunction resize_callback_;
};

}  // namespace fsc