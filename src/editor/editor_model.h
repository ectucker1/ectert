#pragma once

#include "world/world.h"
#include "world/camera.h"
#include "editor/scripting.h"

class EditorModel {

public:
    Scripting scripting;

    World world;
    Camera camera;

    EditorModel();

    void start_render();

};
