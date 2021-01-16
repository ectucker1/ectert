#include "editor_model.h"
#include "processing/render_process.h"
#include "editor/gl_util.h"

EditorModel::EditorModel() : camera(0, 0, 0) {}

void EditorModel::start_render() {
    // Try running the script, and forward errors to the UI
    try {
        auto results = scripting.run_script(script);

        world = results.first;
        camera = results.second;
    } catch (std::exception& e) {
        script_output << e.what() << std::endl;
        return;
    }

    // Scale rendering
    camera.hsize(camera.hsize() * resolution);
    camera.vsize(camera.vsize() * resolution);

    // Create a GL texture to render to
    texture_id = create_render_texture(camera.hsize(), camera.vsize());

    // Start rendering
    process = std::make_unique<RenderProcess>(std::thread::hardware_concurrency());
    process->start_render(camera, world, strata);

    // Update flags
    running = true;
}

void EditorModel::update() {
    if (running) {
        // If the rendering is finished,
        if (process->complete()) {
            // Update flags and clean up
            finished = true;
            running = false;
            process->clean_threads();
        }
    }
}
