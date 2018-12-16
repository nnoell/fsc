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

namespace fsc {
namespace object {
namespace base {
namespace transformer {

// The Transformer base class
class Transformer {
 public:
  // Destructor
  virtual ~Transformer();

  // Gets the name
  std::string GetName() const;

  // Copy Constructor
  Transformer(const Transformer& other);

  // Move Constructor
  Transformer(Transformer && other);

  // Copy-Assign Constructor
  Transformer& operator=(const Transformer& other);

  // Move-Assign Constructr
  Transformer& operator=(Transformer && other);

  // Transforms a model matrix with this transformer
  virtual glm::mat4 Transform(const glm::mat4& model = {}) const = 0;

 protected:
  // Constructor
  Transformer(std::string name);

 private:
  // The name
  std::string name_;
};

}  // namespace transformer
}  // namespace base
}  // namespace object
}  // namespace fsc