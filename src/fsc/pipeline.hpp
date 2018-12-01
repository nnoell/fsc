#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <memory>

// PUBLIC
#include <fsc/external.hpp>

namespace fsc {

// The Pipeline class
class Pipeline final {
 public:
  // Configures the singleton
  static void Configure(const char *vertex_shader_path, const char *fragment_shader_path, const char *geometry_shader_path = nullptr);

  // Resets the singleton
  static void Reset();

  // Gets the instance of the singleton
  static const Pipeline& GetInstance();

 public:
  // Destructor
  virtual ~Pipeline();

  // Uses the pipeline
  void Use() const;

  // Sets a bool
  void SetBool(const char *name, bool value) const;

  // Sets an int
  void SetInt(const char *name, int value) const;

  // Sets a float
  void SetFloat(const char *name, float value) const;

  // Sets a vec2
  void SetVec2(const char *name, const glm::vec2 &value) const;

  // Sets a vect2
  void SetVec2(const char *name, float x, float y) const;

  // Sets a vect3
  void SetVec3(const char *name, const glm::vec3 &value) const;

  // Sets a vect3
  void SetVec3(const char *name, float x, float y, float z) const;

  // Sets a vect4
  void SetVec4(const char *name, const glm::vec4 &value) const;

  // Sets a vect4
  void SetVec4(const char *name, float x, float y, float z, float w) const;

  // Sets a mat2
  void SetMat2(const char *name, const glm::mat2 &mat) const;

  // Sets a mat3
  void SetMat3(const char *name, const glm::mat3 &mat) const;

  // Sets a mat4
  void SetMat4(const char *name, const glm::mat4 &mat) const;

 private:
  // Constructor
  Pipeline();

 private:
  // Copy Constructor
  Pipeline(const Pipeline&) = delete;

  // Move Constructor
  Pipeline(Pipeline &&) = delete;

  // Copy-Assign Constructor
  Pipeline& operator=(const Pipeline&) = delete;

  // Move-Assign Constructr
  Pipeline& operator=(Pipeline &&) = delete;

 private:
  // The instance of the singleton
  static std::unique_ptr<Pipeline> instance_;

  // The vertex shader path
  static const char * vertex_shader_path_;

  // The fragment shader path
  static const char * fragment_shader_path_;

  // The geometry shader path
  static const char * geometry_shader_path_;

 private:
  // The Id
  int id_;
};

}  // namespace fsc