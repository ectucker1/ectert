#pragma once

class Camera;
class World;
class Canvas;

#include <thread>
#include <atomic>
#include <vector>

class RenderProcess {

private:
    std::vector<std::thread> threads;
    volatile std::atomic<int> current {0};

    void render_next(Canvas& canvas, Camera& camera, const World& world, int strata);

public:
    explicit RenderProcess(unsigned int thread_count);

    Canvas render(Camera& camera, const World& world, int strata);

};
