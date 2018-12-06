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

File::File(std::filesystem::path path, bool is_folder, base::TransformData transform_data, glm::mat4 model) :
    base::Complex(
      {
        // The cube
        std::make_shared<base::Polygon>(base::vertices::GetCube(), is_folder ? glm::vec4 {1.0f, 1.0f, 1.0f, 1.0f} : glm::vec4 {0.0f, 1.0f, 1.0f, 1.0f}, true),
        // The file name label
        std::make_shared<base::Ascii>(path.filename().string(), glm::vec4 {0.5, 1.0f, 0.0f, 1.0f}, base::TransformData {{2.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(90.0f), {0.0f, 0.0f, 1.0f}})
        // Extra stuff such as size, date, etc...
      },
      std::move(transform_data),
      std::move(model)
    ),
    path_(std::move(path)),
    is_folder_(is_folder) {
}

File::~File() {
}

std::filesystem::path File::GetPath() const {
  return path_;
}

std::string File::GetName() const {
  return path_.filename().string();
}

bool File::IsFolder() const {
  return is_folder_;
}

}  // namespace object
}  // namespace fsc