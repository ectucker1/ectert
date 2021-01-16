#include "editor_window.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_internal.h"
#include "processing/render_process.h"
#include "editor/gl_util.h"

EditorWindow::EditorWindow() {}

void EditorWindow::render_imgui() {
    // Run model update checks
    model.update();

    // If docking has not yet been initialized
    if (ImGui::DockBuilderGetNode(dock_space) == nullptr) {
        dock_space = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        // Split up the dockspace
        ImGuiID dock_id_right;
        ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_space, ImGuiDir_Left, 0.6f, nullptr, &dock_id_right);
        ImGuiID dock_id_top_left;
        ImGuiID dock_id_bottom_left = ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Down, 0.2f, nullptr, &dock_id_top_left);
        ImGuiID dock_id_top_right;
        ImGuiID dock_id_bottom_right = ImGui::DockBuilderSplitNode(dock_id_right, ImGuiDir_Down, 0.4f, nullptr, &dock_id_top_right);

        // Dock script output and editor
        ImGui::DockBuilderDockWindow("Script Editor", dock_id_top_left);
        ImGui::DockBuilderDockWindow("Render Results", dock_id_top_right);
        ImGui::DockBuilderDockWindow("Render Settings", dock_id_bottom_left);
        ImGui::DockBuilderDockWindow("Script Output", dock_id_bottom_right);

        // Finalize docking
        ImGui::DockBuilderFinish(dock_space);
    } else {
        dock_space = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    }

    // Display the script text editor
    ImGui::Begin("Script Editor");
    ImGui::InputTextMultiline("##script", &model.script, ImVec2(-1, -1));
    ImGui::End();

    // Display render settings
    ImGui::Begin("Render Settings");
    ImGui::PushItemWidth(-1);
    ImGui::Text("Resolution Percent:"); ImGui::SameLine();
    ImGui::SliderFloat("##resolution", &model.resolution, 0, 1, "%.2f");
    ImGui::Text("Strata:"); ImGui::SameLine();
    ImGui::InputInt("##strata", &model.strata, 1, 5);
    ImGui::Spacing();
    // Run the script and start rendering when this button is pressed
    if (ImGui::ButtonEx("Render", ImVec2(0, 0), model.running ? ImGuiButtonFlags_Disabled : ImGuiButtonFlags_PressedOnClickRelease)) {
        model.start_render();
    }
    ImGui::SameLine();
    // TODO Implement stop button
    ImGui::ButtonEx("Stop", ImVec2(0, 0), model.running ? ImGuiButtonFlags_PressedOnClickRelease : ImGuiButtonFlags_Disabled);
    ImGui::PopItemWidth();
    ImGui::End();

    // Display results of rendering
    ImGui::Begin("Render Results");
    if (model.running || model.finished) {
        ImGui::Text("size = %d x %d", model.camera.hsize(), model.camera.vsize());
        ImGui::ProgressBar(model.process->percent_complete());
        uploadTexture(*model.process->canvas, model.texture_id);
        ImGui::Image((void*)(intptr_t)model.texture_id, ImVec2(model.camera.hsize(), model.camera.vsize()));
    }
    ImGui::End();

    // Display errors from the script
    ImGui::Begin("Script Output");
    filter.Draw();
    ImGui::Separator();
    ImGui::TextUnformatted(model.script_output.str().c_str());
    ImGui::End();
}

void EditorWindow::cleanup() {
    if (model.running) {
        model.process->clean_threads();
    }
}
