//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "font.hpp"
#include "pipeline.hpp"

// FreeType vertices are too big so we reduce their size by this factor
#define VERTEX_SCALE_FACTOR 0.02f

namespace fsc {

std::unique_ptr<Font> Font::instance_ = nullptr;

const char * Font::font_path_ = "terminus.ttf";

unsigned int Font::width_ = 1080;

unsigned int Font::height_ = 720;

void Font::Configure(const char *font_path, unsigned int width, unsigned int height) {
  font_path_ = font_path;
  width_ = width;
  height_ = height;
}

void Font::Reset() {
  instance_.reset(new Font {});
}

const Font& Font::GetInstance() {
  if (instance_)
    return *instance_;

  // Create the new instance
  instance_.reset(new Font {});
  return *instance_;
}

Font::Font() :
    projection_(glm::ortho(0.0f, static_cast<GLfloat>(width_), 0.0f, static_cast<GLfloat>(height_))),
    char_vertices_map_() {
    // Init FreeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
      std::runtime_error("Error: failed to init FreeType");

    // Load font
    FT_Face face;
    if (FT_New_Face(ft, font_path_, 0, &face))
      std::runtime_error("Error: failed to load font");

    // Set size to load glyphs
    FT_Set_Pixel_Sizes(face, 0, 48);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++) {
      // Load character glyph 
      if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        std::runtime_error("Error: failed to load char");

      // Generate the texture
      unsigned int texture;
      glGenTextures(1, &texture);

      // Bind the texture
      glBindTexture(GL_TEXTURE_2D, texture);

      // Configure the texture
      glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
      );
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      // Get bearing, size and next position from the glyph
      const glm::ivec2 bearing {face->glyph->bitmap_left, face->glyph->bitmap_top};
      const glm::ivec2 size {face->glyph->bitmap.width, face->glyph->bitmap.rows};
      const float next_position = (face->glyph->advance.x >> 6) * VERTEX_SCALE_FACTOR;

      // Get the dimensions of the character
      const float x = bearing.x * VERTEX_SCALE_FACTOR;
      const float y = (size.y - bearing.y) * VERTEX_SCALE_FACTOR * -1;
      const float w = size.x * VERTEX_SCALE_FACTOR;
      const float h = size.y * VERTEX_SCALE_FACTOR;

      // Create 2 triangles forming a square with the previous dimensions
      char_vertices_map_.insert(std::pair<char, CharData>(c, {
        texture,
        {
          x,     y + h, 0.0f, 1.0f, 0.0f, 0.0f,
          x,     y,     0.0f, 1.0f, 0.0f, 1.0f,
          x + w, y,     0.0f, 1.0f, 1.0f, 1.0f,

          x,     y + h, 0.0f, 1.0f, 0.0f, 0.0f,
          x + w, y,     0.0f, 1.0f, 1.0f, 1.0f,
          x + w, y + h, 0.0f, 1.0f, 1.0f, 0.0f
        },
        6,
        6,
        next_position
      }));

      // Unbind the texture
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

Font::~Font() {
}

const CharData& Font::GetCharData(char c) const {
  return char_vertices_map_.at(c);
}

}  // namespace fsc