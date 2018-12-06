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

// FSC
#include "data.hpp"

namespace fsc {
namespace object {
namespace base {
namespace vertices {

// The Font class
class Font final {
 public:
  // Configures the singleton
  static void Configure(const char *font_path);

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

 private:
  // The char data map
  std::unordered_map<char, CharData> char_vertices_map_;
};

}  // namespace vertices
}  // namespace base
}  // namespace object
}  // namespace fsc