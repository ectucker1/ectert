#pragma once

#include <string>
#include <memory>

class Shape;

std::shared_ptr<Shape> load_obj_group(std::string input);
