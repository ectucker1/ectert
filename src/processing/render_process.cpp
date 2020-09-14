#include "render_process.h"

#include "world/camera.h"
#include "world/world.h"

RenderProcess::RenderProcess(unsigned int thread_count) {
    threads = std::vector<std::thread>(thread_count);
}

Canvas RenderProcess::render(Camera& camera, const World& world, int strata) {
    // Create the canvas to render to
    Canvas canvas = Canvas(camera.hsize, camera.vsize);

    current = 0;

    // Start the threads
    for (int i = 0; i < threads.size(); i++) {
        // Must use std::ref and std::cref when passing to threads by reference
        threads[i] = std::thread(&RenderProcess::render_next, this, std::ref(canvas),
                                 std::ref(camera), std::cref(world), strata);
    }

    // Wait for image to complete
    for (auto& thread : threads) {
        thread.join();
    }

    return canvas;
}

void RenderProcess::render_next(Canvas& canvas, Camera& camera, const World& world, int strata) {
    // Get the next index to render and increment it for other threads
    int next = current++;

    // Keep rendering until the image is finished
    while (next < canvas.width * canvas.height) {
        // Convert index to x and y coordinates
        int x = next % canvas.width;
        int y = next / canvas.width;

        // Trace some rays
        // Stratified sampling, based on https://psgraphics.blogspot.com/2018/10/flavors-of-sampling-in-ray-tracing.html
        Color total = Color(0, 0, 0);
        for (int stratX = 0; stratX < strata; stratX++) {
            for (int stratY = 0; stratY < strata; stratY++) {
                Ray ray = camera.ray_to_strata(x, y, stratX, stratY, strata);
                total = total + world.color_at(ray, 5);
            }
        }
        total = total / (strata * strata);

        // Save color to canvas
        canvas.write_pixel(x, y, total);

        // Advance to next pixel
        next = current++;
    }
}
