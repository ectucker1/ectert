#pragma once

#include <string>
#include <memory>

class Shape;
class Material;

std::shared_ptr<Shape> load_obj_group(std::string input, std::shared_ptr<Material> mat);
