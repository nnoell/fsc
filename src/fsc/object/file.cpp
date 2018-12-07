//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "base/vertices/cube.hpp"
#include "base/polygon.hpp"
#include "base/ascii.hpp"
#include "file.hpp"

namespace fsc {
namespace object {

File::File(std::filesystem::directory_entry entry, base::TransformData transform_data, glm::mat4 model) :
    base::Complex(
      {
        // The cube
        std::make_shared<base::Polygon>(base::vertices::GetCube(), entry.is_directory() ? glm::vec4 {1.0f, 0.7f, 0.0f, 1.0f} : ( entry.is_regular_file() ? glm::vec4 {0.0f, 1.0f, 1.0f, 1.0f} : glm::vec4 {1.0f, 0.0f, 1.0f, 1.0f}), false),
        // The file name label
        std::make_shared<base::Ascii>(entry.path().filename().string(), glm::vec4 {0.5, 1.0f, 0.0f, 1.0f}, base::TransformData {{2.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(90.0f), {0.0f, 0.0f, 1.0f}})
        // Extra stuff such as size, date, etc...
      },
      std::move(transform_data),
      std::move(model)
    ),
    entry_(std::move(entry)) {
  // Check if the entry has a filename
  if (!entry_.path().has_filename())
    throw std::runtime_error("Error: The provided entry dos not have a file name");
}

File::~File() {
}

std::filesystem::path File::GetPath() const {
  return entry_.path();
}

std::string File::GetName() const {
  return entry_.path().filename().string();
}

bool File::IsFolder() const {
  return entry_.is_directory();
}

}  // namespace object
}  // namespace fsc