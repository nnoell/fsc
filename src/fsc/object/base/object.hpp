#pragma once
//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// STL
#include <string>

// PUBLIC
#include <fsc/external.hpp>

// FSC
#include "transformer/model.hpp"
#include "transformer/rotate.hpp"
#include "transformer/scale.hpp"
#include "transformer/translate.hpp"

namespace fsc {
namespace object {
namespace base {

// The Object base class
class Object {
 public:
  // Destructor
  virtual ~Object();

  // Gets the Id
  unsigned int GetId() const;

  // Gets the translate transformer
  const transformer::Translate& GetTransformerTranslate() const;

  // Gets the scale transformer
  const transformer::Scale& GetTransformerScale() const;

  // Gets the rotate transformer
  const transformer::Rotate& GetTransformerRotate() const;

  // Gets the model transformer
  const transformer::Model& GetTransformerModel() const;

  // Translates the object given a translate transformer
  Object& Translate(transformer::Translate translate);

  // Scales the object given a scale transformer
  Object& Scale(transformer::Scale scale);

  // Rotates the object given a rotate transformer
  Object& Rotate(transformer::Rotate rotate);

  // Models the object given a model transformer
  Object& Model(transformer::Model model);

  // Gets the dimension
  glm::vec3 GetDimension() const;

  // Gets the top vertex
  glm::vec3 GetVertexTop() const;

  // Gets the front vertex
  glm::vec3 GetVertexFront() const;

  // Gets the middle vertex
  glm::vec3 GetVertexCenter() const;

  // Gets the max vertex
  virtual glm::vec3 GetVertexMax() const = 0;

  // Gets the min vertex
  virtual glm::vec3 GetVertexMin() const = 0;

  // Draws the object
  virtual void Draw() const = 0;

  // Re-calculates the model matrix
  virtual void RefreshModel() = 0;

 protected:
  // Constructor
  Object(transformer::Translate translate = {}, transformer::Scale scale = {}, transformer::Rotate rotate = {}, transformer::Model model = {});

 private:
  // Copy Constructor
  Object(const Object&) = delete;

  // Move Constructor
  Object(Object &&) = delete;

  // Copy-Assign Constructor
  Object& operator=(const Object&) = delete;

  // Move-Assign Constructr
  Object& operator=(Object &&) = delete;

 private:
  // The Id
  const unsigned int id_;

  // The translate transformer
  transformer::Translate translate_transformer_;

  // The scale transformer
  transformer::Scale scale_transformer_;

  // The rotate transformer
  transformer::Rotate rotate_transformer_;

  // The model transformer
  transformer::Model model_transformer_;
};

}  // namespace base
}  // namespace object
}  // namespace fsc