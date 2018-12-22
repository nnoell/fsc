//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "node.hpp"

namespace fsc {
namespace object {
namespace node {

Details::Details(std::shared_ptr<File> selected_file, unsigned int num_files, std::string path, glm::vec4 color,
      base::transformer::Translate translate, base::transformer::Scale scale, base::transformer::Rotate rotate, base::transformer::Model model) :
    Complex(std::move(translate), std::move(scale), std::move(rotate), std::move(model)),
    selected_file_(std::move(selected_file)),
    num_files_(std::move(num_files)),
    path_(std::move(path)),
    selected_file_section_(std::make_shared<base::Ascii>("", color, base::transformer::Translate {{-1.5f, -3.0f, 0.0f}}, base::transformer::Scale {}, base::transformer::Rotate {-90.0f, {1.0f, 0.0f, 0.0f}})),
    num_files_section_(std::make_shared<base::Ascii>("", color, base::transformer::Translate {{-1.5f, -4.5f, 0.0f}}, base::transformer::Scale {}, base::transformer::Rotate {-90.0f, {1.0f, 0.0f, 0.0f}})),
    path_section_(std::make_shared<base::Ascii>("", color, base::transformer::Translate {{-1.5f, -6.0f, 0.0f}}, base::transformer::Scale {}, base::transformer::Rotate {-90.0f, {1.0f, 0.0f, 0.0f}})) {
  // Add the objects
  AddObject(selected_file_section_);
  AddObject(num_files_section_);
  AddObject(path_section_);

  // Update the objects
  UpdateSelectedFile();
  UpdateNumFiles();
  UpdatePath();
}

Details::~Details() {
}

void Details::SetSelectedFile(std::shared_ptr<File> selected_file) {
  selected_file_ = std::move(selected_file);
  UpdateSelectedFile();
}

void Details::SetNumFiles(unsigned int num_files) {
  num_files_ = std::move(num_files);
  UpdateNumFiles();
}

void Details::SetPath(std::string path) {
  path_ = std::move(path);
  UpdatePath();
}

void Details::UpdateSelectedFile() {
  selected_file_section_->SetAscii("Selected File: " + (selected_file_ ? selected_file_->GetName() : "(NULL)"));
}

void Details::UpdateNumFiles() {
  num_files_section_->SetAscii("Total Files: " + std::to_string(num_files_));
}

void Details::UpdatePath() {
  path_section_->SetAscii("Path: " + path_);
}

}  // namespace node

Node::Node(const File& file, std::shared_ptr<Node> parent,
      base::transformer::Translate translate, base::transformer::Scale scale, base::transformer::Rotate rotate, base::transformer::Model model) :
    Complex(std::move(translate), std::move(scale), std::move(rotate), std::move(model)),
    file_(file),
    folder_(std::make_shared<Folder>(file_.GetPath())),
    parent_(std::move(parent)),
    depth_(!parent_ ? 0 : parent_->GetDepth() + 1),
    cursor_position_({0.0f, 0.0f}),
    origin_line_(std::make_shared<base::Line>(std::vector<glm::vec3>{file_.GetVertexCenter(), folder_->GetVertexCenter()}, glm::vec4 {1.0f, 0.5f, 0.2f, 1.0f})),
    details_(std::make_shared<node::Details>(nullptr, 0, file_.GetPath().string())) {
  AddObject(folder_);
  // AddObject(origin_line_);
  AddObject(details_);

  // Update the node
  Update();
}

Node::~Node() {
}

const File& Node::GetFile() const {
  return file_;
}

const std::shared_ptr<Folder> Node::GetFolder() const {
  return folder_;
}

std::shared_ptr<Node> Node::GetParent() const {
  return parent_;
}

unsigned int Node::GetDepth() const {
  return depth_;
}

std::shared_ptr<File> Node::GetSelectedFile() const {
  return folder_->GetFile(cursor_position_.x, cursor_position_.y);
}

void Node::SelectFileUp() {
  // Check for the new position
  const unsigned int new_y = cursor_position_.y + 1;
  if (new_y < 0 || new_y >= folder_->GetNumCols())
    return;
  const unsigned int pos = cursor_position_.x + (new_y * folder_->GetNumCols());
  if (pos < 0 || pos >= folder_->GetNumFiles())
    return;

  // Update the cursor
  cursor_position_.y++;
  Update();
}

void Node::SelectFileDown() {
  if (cursor_position_.y <= 0)
    return;

  // Check for the new position
  const unsigned int new_y = cursor_position_.y - 1;
  if (new_y < 0 || new_y >= folder_->GetNumCols())
    return;
  const unsigned int pos = cursor_position_.x + (new_y * folder_->GetNumCols());
  if (pos < 0 || pos >= folder_->GetNumFiles())
    return;

  // Update the cursor
  cursor_position_.y--;
  Update();
}
void Node::SelectFileLeft() {
  if (cursor_position_.x <= 0)
    return;

  // Check for the new position
  const unsigned int new_x = cursor_position_.x - 1;
  if (new_x < 0 || new_x >= folder_->GetNumCols())
    return;
  const unsigned int pos = new_x + (cursor_position_.y * folder_->GetNumCols());
  if (pos < 0 || pos >= folder_->GetNumFiles())
    return;

  // Update the cursor
  cursor_position_.x--;
  Update();
}

void Node::SelectFileRight() {
  // Check for the new position
  const unsigned int new_x = cursor_position_.x + 1;
  if (new_x < 0 || new_x >= folder_->GetNumCols())
    return;
  const unsigned int pos = new_x + (cursor_position_.y * folder_->GetNumCols());
  if (pos < 0 || pos >= folder_->GetNumFiles())
    return;

  // Update the cursor
  cursor_position_.x++;
  Update();
}

void Node::Update() {
  // Get the selected file
  const std::shared_ptr<File> selected_file = GetSelectedFile();
  if (!selected_file)
    return;

  // Update the details
  details_->SetSelectedFile(std::move(selected_file));
  details_->SetNumFiles(folder_->GetNumFiles());
}

}  // namespace object
}  // namespace fsc