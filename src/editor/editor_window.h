#pragma once

#include <iostream>
#include "editor_model.h"
#include "imgui.h"

class EditorWindow {

public:
    EditorModel model;

    ImGuiID dock_space;

    ImGuiTextFilter filter;

    EditorWindow();

    void render_imgui();
    void cleanup();

};
