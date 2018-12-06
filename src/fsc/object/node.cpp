//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "node.hpp"

namespace fsc {
namespace object {

Node::Node(std::filesystem::path path, std::shared_ptr<Node> parent, base::TransformData transform_data, glm::mat4 model) :
    Complex({}, std::move(transform_data), std::move(model)),
    folder_(std::make_shared<Folder>(std::move(path))),
    parent_(std::move(parent)),
    children_({}) {
}

Node::~Node() {
}

}  // namespace object
}  // namespace fsc