#pragma once

#include "world/world.h"
#include "world/camera.h"
#include "editor/scripting.h"

class RenderProcess;

class EditorModel {

public:
    std::unique_ptr<RenderProcess> process;

    World world;
    Camera camera;

    std::string script;
    Scripting scripting;
    std::stringstream script_output;

    float resolution = 1;
    int strata = 8;

    bool running = false;
    bool finished = false;
    int texture_id;

    EditorModel();

    void start_render();
    void update();

};
