#include <iostream>
#include <cmath>
#include "editor/editor_window.h"
#include "editor/editor_model.h"
#include "processing/render_process.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl2.h"
#include "GLFW/glfw3.h"
#include "main_scene.h"

// Print any errors from IMGUI
void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

int main() {
    // Initialize GLFW
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        return -1;
    }

    // Create a GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Ectert Raytracer", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Get monitor DPI scale
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    float xscale, yscale;
    glfwGetMonitorContentScale(monitor, &xscale, &yscale);
    float scale = std::fmax(xscale, yscale);

    // Initialize IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.IniFilename = nullptr;

    ImGui::StyleColorsDark();
    ImGui::GetStyle().ScaleAllSizes(scale);

    // Attach IMGUI to GLFW window
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    // Create the editor window
    EditorWindow editor = EditorWindow();

    // While the window hasn't been closed
    while (!glfwWindowShouldClose(window))
    {
        // Poll input
        glfwPollEvents();

        // Start a new frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Show demo window
        //ImGui::ShowDemoWindow();

        // Render editor elements
        editor.render_imgui();

        // Generate IMGUI output
        ImGui::Render();

        // Resize viewport and clear screen
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // Actually render the UI
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        // Swap frame into the GLFW window
        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    // Clean up render process
    editor.cleanup();

    // Shutdown IMGUI
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Shutdown GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
