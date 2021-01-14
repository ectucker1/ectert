#include "editor_model.h"

EditorModel::EditorModel() : camera(0, 0, 0) {}

void EditorModel::start_render() {
    // TODO Get this script from the UI
    const std::string script = R""(
world = World.new()

test_sphere = make_sphere(scaling(15, 15, 15))
test_sphere.material = make_lambertian(Color.new(1, 0, 0))
world.objects:add(test_sphere)

world.background = make_gradient_background(Color.new(0, 0, 1), Color.new(1, 1, 1))

camera = Camera.new(256, 256, math.pi / 3)
camera.transform = view_transform(Tuple.new(20, 20, 20, 1), Tuple.new(0, 0, 0, 1), Tuple.new(0, 1, 0, 0))
    )"";

    auto results = scripting.run_script(script);

    world = results.first;
    camera = results.second;
}
