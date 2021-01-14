#pragma once

#include <memory>
#include "sol/sol.hpp"
#include "world/world.h"
#include "world/camera.h"

namespace sol
{
    class state;
}

class Scripting {

public:
    Scripting();

    std::pair<World, Camera> run_script(const std::string& script);

private:
    std::unique_ptr<sol::state> _lua;

    void initialize_lua();

};
