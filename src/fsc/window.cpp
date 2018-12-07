//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <sstream>

// FSC
#include "window.hpp"
#include "fps.hpp"

namespace fsc {

// Initializes GLFW
std::unique_ptr<const int, void(*)(const int*)> InitGlfw() {
  // Init GLFW
  const int res = glfwInit();
  if (res != GLFW_TRUE)
    throw std::runtime_error("Error: Ccould not initialize GLFW");

  // Configure
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  return {new int {res}, [](const int *res) { glfwTerminate(); delete res;}};
}

Window::Window(unsigned int width, unsigned int height, std::string title) : 
    glfw_(InitGlfw()),
    title_(std::move(title)),
    window_(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr), glfwDestroyWindow),
    key_callback_map_mutex_(),
    mouse_callback_mutex_(),
    key_callback_map_({{GLFW_KEY_ESCAPE, {[&](){glfwSetWindowShouldClose(window_.get(), true);}, false, false}}}),
    mouse_callback_(nullptr) {
  if (!window_)
    throw std::runtime_error("Error: Could not create GLFW window");

  // Set the user pointer
  glfwSetWindowUserPointer(window_.get(), this);

  // Set the mouse callback
  glfwSetCursorPosCallback(window_.get(), [](GLFWwindow* win, double x, double y){
    Window *thiz = reinterpret_cast<Window *>(glfwGetWindowUserPointer(win));
    if (thiz)
      thiz->CallMouseCallback(x, y);
  });

  // Set resize callback
  glfwSetFramebufferSizeCallback(window_.get(), [](GLFWwindow* win, int w, int h){
    Window *thiz = reinterpret_cast<Window *>(glfwGetWindowUserPointer(win));
    if (thiz)
      thiz->CallResizeCallback(w, h);
  });

  // Make the window current
  glfwMakeContextCurrent(window_.get());

  // Init Glad
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    throw std::runtime_error("Error: Could not load GLAD");
}

Window::~Window() {
}

void Window::AddKeyCallback(int key, KeyFunction pressed, bool block_until_released) {
  std::unique_lock<std::mutex> lock(key_callback_map_mutex_);

  // Add the new callback
  key_callback_map_[key] = {std::move(pressed), block_until_released, false};
}

void Window::SetMouseCallback(MouseFunction callback) {
  std::unique_lock<std::mutex> lock(mouse_callback_mutex_);

  // Set the new callback
  mouse_callback_ = callback;
}

void Window::SetResizeCallback(ResizeFunction callback) {
  std::unique_lock<std::mutex> lock(resize_callback_mutex_);

  // Set the new callback
  resize_callback_ = callback;
}

void Window::CallMouseCallback(double x, double y) {
  std::unique_lock<std::mutex> lock(mouse_callback_mutex_);

  // Call the callback
  if (mouse_callback_)
    mouse_callback_(x, y);
}

void Window::CallResizeCallback(int w, int h) {
  std::unique_lock<std::mutex> lock(resize_callback_mutex_);

  // Call the callback
  if (resize_callback_)
    resize_callback_(w, h);
}

void Window::Render(RenderFunction render_function) {
  // Create the FPS counter
  Fps fps {};

  // Render loop
  while (!glfwWindowShouldClose(window_.get())) {
    // Update the FPS
    fps.Update();

    // Update the windows title
    UpdateWindowTitle(fps.GetFps(), fps.GetMillisecondPerFrame());

    // Process window input
    ProcessInput();

    // Call the render function
    render_function();

    // Swap window buffers
    glfwSwapBuffers(window_.get());

    // Poll events
    glfwPollEvents();
  }
}

void Window::UpdateWindowTitle(double fps, double msframe) {
  std::stringstream ss;
  ss << title_ << " | " << std::floor(fps) << " fps | " << std::floor(msframe) << " ms/fps";
  glfwSetWindowTitle(window_.get(), ss.str().c_str());
}

void Window::ProcessInput() {
  std::unique_lock<std::mutex> lock(key_callback_map_mutex_);

  // Call the specific handler
  for (auto&& pair : key_callback_map_) {
    // The key press handler
    if (glfwGetKey(window_.get(), pair.first) == GLFW_PRESS && !pair.second.is_blocked) {
      pair.second.press_callback();

      // Block the key until it is released if block_until_released is true
      if (pair.second.block_until_released)
        pair.second.is_blocked = true;
    }

    // The key release handler
    if (glfwGetKey(window_.get(), pair.first) == GLFW_RELEASE)
      pair.second.is_blocked = false;
  }
}

}  // namespace fsc