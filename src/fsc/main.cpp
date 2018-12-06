//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "object/base/vertices/font.hpp"
#include "object/base/ascii.hpp"
#include "object/base/line.hpp"
#include "object/folder.hpp"
#include "object/file.hpp"
#include "object/plane.hpp"
#include "window.hpp"
#include "world.hpp"
#include "pipeline.hpp"
#include "camera.hpp"

// The window resulution
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

// The font path
#define FONT_PATH "..\\fonts\\terminus.ttf"

// The shader location
#define SHADER_VERTEX_PATH "..\\src\\fsc\\shader\\vertex.glsl"
#define SHADER_FRAGMENT_PATH "..\\src\\fsc\\shader\\fragment.glsl"

namespace fsc {

// The namespaced main function
bool Main(int argc, char* argv[]) {
  std::cout << "FSC " FSC_VERSION << std::endl;

  try {
    // Create the window
    Window window {WINDOW_WIDTH, WINDOW_HEIGHT, "FSC " FSC_VERSION};
    window.SetResizeCallback([](int width, int height) { glViewport(0, 0, width, height); });

    // Configure the font
    object::base::vertices::Font::Configure(FONT_PATH, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Configure the shaders
    Pipeline::Configure(SHADER_VERTEX_PATH, SHADER_FRAGMENT_PATH);
    Pipeline::GetInstance().Use();

    // Create the camera
    Camera camera {};

    // Create the world
    World world {WINDOW_WIDTH, WINDOW_HEIGHT, {0.1f, 0.1f, 0.1f, 0.1f}};

    // Bind the keys camera keys
    window.AddKeyCallback(GLFW_KEY_W, std::bind(&Camera::MoveFront, &camera));
    window.AddKeyCallback(GLFW_KEY_S, std::bind(&Camera::MoveBack, &camera));
    window.AddKeyCallback(GLFW_KEY_A, std::bind(&Camera::MoveLeft, &camera));
    window.AddKeyCallback(GLFW_KEY_D, std::bind(&Camera::MoveRight, &camera));
    window.AddKeyCallback(GLFW_KEY_SPACE, std::bind(&Camera::MoveUp, &camera));
    window.AddKeyCallback(GLFW_KEY_X, std::bind(&Camera::MoveDown, &camera));
    window.AddKeyCallback(GLFW_KEY_C, std::bind(&Camera::LookUp, &camera));
    window.AddKeyCallback(GLFW_KEY_Z, std::bind(&Camera::LookDown, &camera));
    window.AddKeyCallback(GLFW_KEY_Q, std::bind(&Camera::LookLeft, &camera));
    window.AddKeyCallback(GLFW_KEY_E, std::bind(&Camera::LookRight, &camera));
    window.AddKeyCallback(GLFW_KEY_R, std::bind(&Camera::SetPosition, &camera, glm::vec3 {0.0f, 2.0f, 3.0f}));
    window.AddKeyCallback(GLFW_KEY_F, std::bind(&Camera::SetFront, &camera, glm::vec3 {0.0f, 0.0f, -1.0f}));

    // Bind the world keys
    window.AddKeyCallback(GLFW_KEY_UP, std::bind(&World::SelectUp, &world), true);
    window.AddKeyCallback(GLFW_KEY_DOWN, std::bind(&World::SelectDown, &world), true);
    window.AddKeyCallback(GLFW_KEY_LEFT, std::bind(&World::SelectLeft, &world), true);
    window.AddKeyCallback(GLFW_KEY_RIGHT, std::bind(&World::SelectRight, &world), true);

    // Render
    window.Render([&](){
      // Update the camera
      camera.Update();

      // Update the world
      world.Update();
    });

    // Exit
    return true;
  } catch (std::runtime_error e) {
    std::cout << ">> FSC error: " << e.what() << std::endl;
    return false;
  } catch (...) {
    std::cout << ">> FSC error" << std::endl;
    return false;
  }
}

}  // namespace fsc

// The main function
int main(int argc, char* argv[]) {
  return fsc::Main(argc, argv) ? 0 : -1;
}