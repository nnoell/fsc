#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <unordered_map>
#include <string>
#include <memory>

// PUBLIC
#include <fsc/external.hpp>

namespace fsc {
namespace object {
namespace vertices {

// The char data type
struct CharData {
  // The vertices
  std::shared_ptr<const float []> vertices;

  // The number of vertices
  unsigned int num_vertices;

  // The stride
  unsigned int stride;

  // The position for the next character
  float next_position;

  // The texture
  unsigned int texture;
};

// The Font class
class Font final {
 public:
  // Configures the singleton
  static void Configure(const char *font_path, unsigned int width, unsigned int height);

  // Resets the singleton
  static void Reset();

  // Gets the instance of the singleton
  static const Font& GetInstance();

 public:
  // Destructor
  virtual ~Font();

  // Gets the char vertices of a character
  const CharData& GetCharData(char c) const;

 private:
  // Constructor
  Font();

 private:
  // Copy Constructor
  Font(const Font&) = delete;

  // Move Constructor
  Font(Font &&) = delete;

  // Copy-Assign Constructor
  Font& operator=(const Font&) = delete;

  // Move-Assign Constructr
  Font& operator=(Font &&) = delete;

 private:
  // The instance of the singleton
  static std::unique_ptr<Font> instance_;

  // The font path
  static const char * font_path_;

  // The width of the screen
  static unsigned int width_;

  // The height of the screen
  static unsigned int height_;

 private:
  // Projection
  glm::mat4 projection_;

  // The char data map
  std::unordered_map<char, CharData> char_vertices_map_;
};

}  // namespace vertices
}  // namespace object
}  // namespace fsc