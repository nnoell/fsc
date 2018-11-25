//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "pipeline.hpp"
#include "shader.hpp"

namespace fsc {

std::unique_ptr<Pipeline> Pipeline::instance_ = nullptr;

const char * Pipeline::vertex_shader_path_ = "vertex.glsl";

const char * Pipeline::fragment_shader_path_ = "fragment.glsl";

const char * Pipeline::geometry_shader_path_ = nullptr;

void Pipeline::Configure(const char *vertex_shader_path, const char *fragment_shader_path, const char *geometry_shader_path) {
  vertex_shader_path_ = vertex_shader_path;
  fragment_shader_path_ = fragment_shader_path;
  geometry_shader_path_ = geometry_shader_path;
}

void Pipeline::Reset() {
  instance_.reset(new Pipeline {});
}

const Pipeline& Pipeline::GetInstance() {
  if (instance_)
    return *instance_;

  // Create the new instance
  instance_.reset(new Pipeline {});
  return *instance_;
}

Pipeline::Pipeline() :
    id_(glCreateProgram()) {
  if (!id_)
    throw std::runtime_error("Error: Failed to create program");
  if (!vertex_shader_path_ || !fragment_shader_path_)
    throw std::runtime_error("Error: Need a vertex and fragment shader to create a program");

  // Create the shaders and add them to the program
  Shader vertex_shader(vertex_shader_path_, GL_VERTEX_SHADER);
  glAttachShader(id_, vertex_shader.GetId());
  Shader fragment_shader(fragment_shader_path_, GL_FRAGMENT_SHADER);
  glAttachShader(id_, fragment_shader.GetId());
  if (geometry_shader_path_) {
    Shader geometry_shader(geometry_shader_path_, GL_FRAGMENT_SHADER);
    glAttachShader(id_, geometry_shader.GetId());
  }

  // Link the shaders
  glLinkProgram(id_);

  // Check for linking errors
  int res = 0;
  glGetProgramiv(id_, GL_LINK_STATUS, &res);
  if (!res) 
    throw std::runtime_error("Error: Failed to link program");
}

Pipeline::~Pipeline() {
  glDeleteProgram(id_);
}

void Pipeline::Use() const {
  glUseProgram(id_);
}

void Pipeline::SetBool(const char *name, bool value) const {
  glUniform1i(glGetUniformLocation(id_, name), (int)value);
}

void Pipeline::SetInt(const char *name, int value) const {
  glUniform1i(glGetUniformLocation(id_, name), value);
}

void Pipeline::SetFloat(const char *name, float value) const {
  glUniform1f(glGetUniformLocation(id_, name), value);
}

void Pipeline::SetVec2(const char *name, const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(id_, name), 1, &value[0]);
}

void Pipeline::SetVec2(const char *name, float x, float y) const {
  glUniform2f(glGetUniformLocation(id_, name), x, y);
}

void Pipeline::SetVec3(const char *name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(id_, name), 1, &value[0]);
}

void Pipeline::SetVec3(const char *name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(id_, name), x, y, z);
}

void Pipeline::SetVec4(const char *name, const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(id_, name), 1, &value[0]);
}

void Pipeline::SetVec4(const char *name, float x, float y, float z, float w) const {
  glUniform4f(glGetUniformLocation(id_, name), x, y, z, w);
}

void Pipeline::SetMat2(const char *name, const glm::mat2 &mat) const {
  glUniformMatrix2fv(glGetUniformLocation(id_, name), 1, GL_FALSE, &mat[0][0]);
}

void Pipeline::SetMat3(const char *name, const glm::mat3 &mat) const {
  glUniformMatrix3fv(glGetUniformLocation(id_, name), 1, GL_FALSE, &mat[0][0]);
}

void Pipeline::SetMat4(const char *name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE, &mat[0][0]);
}

}  // namespace fsc