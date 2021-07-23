#include "editor_window.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_internal.h"

EditorWindow::EditorWindow() {}

void EditorWindow::render_imgui() {
    // Run model render loop
    model.render();

    // Display render settings
    ImGui::Begin("Render Settings");
    ImGui::PushItemWidth(-1);
    ImGui::Text("Render Width:");
    ImGui::InputInt("##width", &model.width, 1, 10);
    ImGui::Text("Render Height:");
    ImGui::InputInt("##height", &model.height, 1, 10);
    ImGui::Text("Samples:");
    ImGui::InputInt("##samples", &model.samples, 1, 2);
    ImGui::Spacing();
    ImGui::PopItemWidth();
    ImGui::End();

    // Display errors from the script
    ImGui::Begin("Renderer Output");
    filter.Draw();
    ImGui::Separator();
    ImGui::TextUnformatted("Error Log Here");
    ImGui::End();
}

void EditorWindow::cleanup() {

}
