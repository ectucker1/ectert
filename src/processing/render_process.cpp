#include "render_process.h"

#include "world/camera.h"
#include "world/world.h"

RenderProcess::RenderProcess(unsigned int thread_count) {
    current = std::make_unique<std::atomic<int>>(0);
    finished_threads = std::make_unique<std::atomic<int>>(0);
    threads = std::vector<std::unique_ptr<std::thread>>(thread_count);
}

void RenderProcess::start_render(Camera& camera, const World& world, int strata) {
    // Create the canvas to render to
    canvas = std::make_unique<Canvas>(camera.hsize, camera.vsize);

    finished_threads->operator=(0);
    current->operator=(0);

    // Start the threads
    for (int i = 0; i < threads.size(); i++) {
        // Must use std::ref and std::cref when passing to threads by reference
        threads[i] = std::make_unique<std::thread>(&RenderProcess::render_next, this, std::ref(camera), std::cref(world), strata);
    }
}

void RenderProcess::render_next(Camera& camera, const World& world, int strata) {
    // Get the next index to render and increment it for other threads
    int next = current->operator++();

    // Keep rendering until the image is finished
    while (next < canvas->width * canvas->height) {
        // Convert index to x and y coordinates
        int x = next % canvas->width;
        int y = next / canvas->width;

        // Trace some rays
        // Stratified sampling, based on https://psgraphics.blogspot.com/2018/10/flavors-of-sampling-in-ray-tracing.html
        Color total = Color(0, 0, 0);
        for (int stratX = 0; stratX < strata; stratX++) {
            for (int stratY = 0; stratY < strata; stratY++) {
                Ray ray = camera.ray_to_strata(x, y, stratX, stratY, strata);
                total = total + world.color_at(ray, 5);
            }
        }

        // Gamma correction
        total = total / (strata * strata);
        total.r = sqrtf(total.r);
        total.g = sqrtf(total.g);
        total.b = sqrtf(total.b);

        // Save color to canvas
        canvas->write_pixel(x, y, total);

        // Advance to next pixel
        next = current->operator++();
    }

    // Add this to the number of finished threads
    finished_threads->operator++();
}

float RenderProcess::percent_complete() const {
    return (float) *current / (canvas->width * canvas->height);
}

bool RenderProcess::complete() const {
    return *finished_threads >= threads.size();
}

void RenderProcess::clean_threads() {
    for (int i = 0; i < threads.size(); i++) {
        threads[i]->join();
    }
}
