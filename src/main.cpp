#include <iostream>
#include <cmath>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl2.h"
#include "GLFW/glfw3.h"
#include "canvas.h"

// Print any errors from IMGUI
void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

int create_render_texture(int width, int height) {
    Canvas canvas = Canvas(width, height);

    // Create a OpenGL texture identifier
    GLuint render_texture;
    glGenTextures(1, &render_texture);
    glBindTexture(GL_TEXTURE_2D, render_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, canvas.image());

    return render_texture;
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

    ImGui::StyleColorsDark();
    ImGui::GetStyle().ScaleAllSizes(scale);

    // Attach IMGUI to GLFW window
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    // Create canvas to render to
    Canvas canvas = Canvas(1920, 1080);
    int texture = create_render_texture(canvas.width, canvas.height);

    // While the window hasn't been closed
    while (!glfwWindowShouldClose(window))
    {
        // Poll input
        glfwPollEvents();

        // Start a new frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Write random data to the canvas
        canvas.write_pixel(rand() % canvas.width, rand() % canvas.height, Color(1, 1, 1));

        // Reupload the image data
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, canvas.width, canvas.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, canvas.image());

        // Create demo window
        ImGui::ShowMetricsWindow();
        ImGui::Begin("Rendering Results");
        ImGui::Text("size = %d x %d", canvas.width, canvas.height);
        ImGui::Image((void*)(intptr_t)texture, ImVec2(canvas.width, canvas.height));
        ImGui::End();

        // Generate IMGUI
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

    // Shutdown IMGUI
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Shutdown GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
