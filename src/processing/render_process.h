#pragma once

class Camera;
class World;
class Canvas;

#include <thread>
#include <atomic>
#include <vector>

class RenderProcess {

private:
    std::vector<std::unique_ptr<std::thread>> threads;
    std::unique_ptr<std::atomic<int>> finished_threads;

    std::unique_ptr<std::atomic<int>> current;

    void render_next(Camera& camera, const World& world, int strata);

public:
    std::unique_ptr<Canvas> canvas;

    explicit RenderProcess(unsigned int thread_count);

    void start_render(Camera& camera, const World& world, int strata);

    float percent_complete() const;
    bool complete() const;

    void clean_threads();

};
