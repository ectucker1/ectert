#include "render_process.h"

#include "world/camera.h"
#include "world/world.h"

RenderProcess::RenderProcess(unsigned int thread_count) {
    threads = std::vector<std::thread>(thread_count);
}

Canvas RenderProcess::render(const Camera& camera, const World& world) {
    // Create the canvas to render to
    Canvas canvas = Canvas(camera.hsize, camera.vsize);

    current = 0;

    // Start the threads
    for (int i = 0; i < threads.size(); i++) {
        // Must use std::ref and std::cref when passing to threads by reference
        threads[i] = std::thread(&RenderProcess::render_next, this, std::ref(canvas), std::cref(camera), std::cref(world));
    }

    // Wait for image to complete
    for (auto& thread : threads) {
        thread.join();
    }

    return canvas;
}

void RenderProcess::render_next(Canvas& canvas, const Camera& camera, const World& world) {
    // Get the next index to render and increment it for other threads
    int next = current++;

    // Keep rendering until the image is finished
    while (next < canvas.width * canvas.height) {
        // Convert index to x and y coordinates
        int x = next % canvas.width;
        int y = next / canvas.width;

        // Trace some rays
        Ray ray = camera.ray_to_pixel(x, y);
        Color color = world.color_at(ray, 5);

        // Save color to canvas
        canvas.write_pixel(x, y, color);

        // Advance to next pixel
        next = current++;
    }
}
