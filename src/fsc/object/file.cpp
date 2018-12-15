//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "base/vertices/cube.hpp"
#include "file.hpp"

namespace fsc {
namespace object {

File::File(std::filesystem::directory_entry entry, base::TransformData transform_data) :
    base::Complex(std::move(transform_data)),
    entry_(std::move(entry)),
    base_(std::make_shared<base::Polygon>(base::vertices::GetCube(), entry_.is_directory() ? glm::vec4 {0.4f, 1.0f, 0.6f, 1.0f} : glm::vec4 {0.4f, 0.4f, 0.4f, 1.0f}, false, base::TransformData {{0.0f, 0.0f, 0.0f}, {1.5f, 0.5f, 1.5}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}})),
    cube_(std::make_shared<base::Polygon>(base::vertices::GetCube(), (entry_.is_directory()  || entry_.is_regular_file()) ? glm::vec4 {0.3f, 0.6f, 1.0f, 1.0f} : glm::vec4 {0.5f, 0.5f, 0.5f, 1.0f}, false, base::TransformData {{0.0f, 1.5f, 0.0f}, {1.0f, 1.0f, 1.0}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}})) {
  // Add the objects
  AddObject(base_);
  AddObject(cube_);
}

File::~File() {
}

std::filesystem::path File::GetPath() const {
  return entry_.path();
}

std::string File::GetName() const {
  // Return empty if the file does not have a name
  if (!entry_.path().has_filename())
    return "";

  return entry_.path().filename().string();
}

bool File::IsFolder() const {
  return entry_.is_directory();
}

}  // namespace object
}  // namespace fsc