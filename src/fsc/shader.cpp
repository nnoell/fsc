//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "shader.hpp"

namespace fsc {

Shader::Shader(const char *source_path, GLenum type) :
    id_(glCreateShader(type)) {
  if (!id_)
    throw std::runtime_error("Error: Failed to create shader");

  // Read the source file
  std::ifstream file;
  file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  file.open(source_path, std::ios::in);
  std::stringstream source_stream;
  source_stream << file.rdbuf();
  std::string source = source_stream.str();
  file.close();

  // Set the source
  const char *shader_source = source.c_str();
  glShaderSource(id_, 1, &shader_source, nullptr);

  // Compile
  glCompileShader(id_);

  // Check for compile error
  int res = 0;
  glGetShaderiv(id_, GL_COMPILE_STATUS, &res);
  if (!res)
    throw std::runtime_error("Error: Failed to compile shader");
}

Shader::~Shader() {
  glDeleteShader(id_);
}

int Shader::GetId() const {
  return id_;
}

}  // namespace fsc