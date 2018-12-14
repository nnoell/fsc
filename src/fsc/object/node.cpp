//----------------------------------------------------------------------------------------------------------------------
// Copyright   :  (c) Julian Bouzas 2018
// License     :  BSD3-style (see LICENSE)
// Maintainer  :  Julian Bouzas - nnoell3[at]gmail.com
//----------------------------------------------------------------------------------------------------------------------

// FSC
#include "node.hpp"
#include "base/vertices/pyramid.hpp"

namespace fsc {
namespace object {
namespace node {

Details::Details(std::shared_ptr<File> selected_file, unsigned int num_files, std::string path, glm::vec4 color, base::TransformData transform_data , glm::mat4 model) :
    Complex({}, std::move(transform_data), std::move(model)),
    selected_file_(std::move(selected_file)),
    num_files_(std::move(num_files)),
    path_(std::move(path)),
    selected_file_section_(std::make_shared<base::Ascii>("", color, base::TransformData {{-1.5f, -3.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}})),
    num_files_section_(std::make_shared<base::Ascii>("", color, base::TransformData {{-1.5f, -4.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}})),
    path_section_(std::make_shared<base::Ascii>("", color, base::TransformData {{-1.5f, -6.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(-90.0f), {1.0f, 0.0f, 0.0f}})) {
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

Cursor::Cursor(std::string text, base::TransformData transform_data, glm::mat4 model) :
    Complex({}, std::move(transform_data), std::move(model)),
      pointer_(std::make_shared<base::Polygon>(base::vertices::GetPyramid(), glm::vec4 {1.0f, 0.5f, 0.2f, 1.0f}, false, base::TransformData {{0.0f, -1.0f, 0.0f}, {1.5f, 1.5f, 1.5f}, glm::radians(180.0f), {0.0f, 0.0f, 1.0f}})),
      text_(std::make_shared<base::Ascii>(std::move(text), glm::vec4 {1.0f, 0.5f, 0.2f, 1.0f}, base::TransformData {{0.0f, 4.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}})) {
  // Add the objects
  AddObject(pointer_);
  AddObject(text_);
}

Cursor::~Cursor() {
}

std::string Cursor::GetText() const {
  return text_->GetAscii();
}

void Cursor::SetText(std::string text) {
  text_->SetAscii(std::move(text));
}

}  // namespace node

Node::Node(const File& file, std::shared_ptr<Node> parent, base::TransformData transform_data, glm::mat4 model) :
    Complex({}, std::move(transform_data), std::move(model)),
    file_(file),
    folder_(std::make_shared<Folder>(file_.GetPath(), base::TransformData {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}}, glm::mat4 {})),
    parent_(std::move(parent)),
    depth_(!parent_ ? 0 : parent_->GetDepth() + 1),
    cursor_position_({0.0f, 0.0f}),
    origin_line_(std::make_shared<base::Line>(std::vector<glm::vec3>{file_.GetVertexMiddle(), folder_->GetVertexMiddle()}, glm::vec4 {1.0f, 0.5f, 0.2f, 1.0f})),
    cursor_(std::make_shared<node::Cursor>("")),
    details_(std::make_shared<node::Details>(nullptr, 0, file_.GetPath().string())),
    selected_node_(nullptr),
    opened_nodes_() {
  AddObject(folder_);
  // AddObject(origin_line_);
  AddObject(cursor_);
  AddObject(details_);

  // Update the node
  Update();
}

Node::~Node() {
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

// Opens the selected folder
std::shared_ptr<Node> Node::OpenSelectedFile() {
  std::shared_ptr<File> selected_file = folder_->GetFile(cursor_position_.x, cursor_position_.y);
  if (!selected_file)
    return nullptr;

  return OpenFile(*selected_file);
}

std::shared_ptr<Node> Node::OpenFile(const File& file) {
  // Check if the file is a folder
  if (!file.IsFolder())
    return nullptr;

  // Check if the folder contains the file
  const unsigned int file_id = file.GetId();
  if (!folder_->ContainsFile(file_id))
    return nullptr;

  // Check if the file is already open
  std::unordered_map<unsigned int, std::shared_ptr<Node>>::const_iterator it = opened_nodes_.find(file_id);
  if (it != opened_nodes_.end())
    return it->second;

  // Create and add the node to the list
  selected_node_ = std::make_shared<Node>(file, shared_from_this());
  opened_nodes_[file_id] = selected_node_;

  return selected_node_;
}

void Node::Update() {
  // Get the selected file
  const std::shared_ptr<File> selected_file = folder_->GetFile(cursor_position_.x, cursor_position_.y);
  if (!selected_file)
    return;

  // Update the cursor and details
  cursor_->SetText(selected_file->GetName());
  cursor_->SetTransformData({selected_file->GetVertexTop(), {1.0f, 1.0f, 1.0}, glm::radians(0.0f), {1.0f, 1.0f, 1.0f}});
  details_->SetSelectedFile(std::move(selected_file));
  details_->SetNumFiles(folder_->GetNumFiles());
}

void Node::MoveCursorUp() {
  // Check for the new position
  const int new_y = cursor_position_.y + 1;
  if (new_y < 0 || new_y >= folder_->GetNumCols())
    return;
  const int pos = cursor_position_.x + (new_y * folder_->GetNumCols());
  if (pos < 0 || pos >= folder_->GetNumFiles())
    return;

  // Update the cursor
  cursor_position_.y++;
  Update();
}

void Node::MoveCursorDown() {
  // Check for the new position
  const int new_y = cursor_position_.y - 1;
  if (new_y < 0 || new_y >= folder_->GetNumCols())
    return;
  const int pos = cursor_position_.x + (new_y * folder_->GetNumCols());
  if (pos < 0 || pos >= folder_->GetNumFiles())
    return;

  // Update the cursor
  cursor_position_.y--;
  Update();
}

void Node::MoveCursorLeft() {
  // Check for the new position
  const int new_x = cursor_position_.x - 1;
  if (new_x < 0 || new_x >= folder_->GetNumCols())
    return;
  const int pos = new_x + (cursor_position_.y * folder_->GetNumCols());
  if (pos < 0 || pos >= folder_->GetNumFiles())
    return;

  // Update the cursor
  cursor_position_.x--;
  Update();
}

void Node::MoveCursorRight() {
  // Check for the new position
  const int new_x = cursor_position_.x + 1;
  if (new_x < 0 || new_x >= folder_->GetNumCols())
    return;
  const int pos = new_x + (cursor_position_.y * folder_->GetNumCols());
  if (pos < 0 || pos >= folder_->GetNumFiles())
    return;

  // Update the cursor
  cursor_position_.x++;
  Update();
}

}  // namespace object
}  // namespace fsc