#include "scripting.h"
#include <functional>
#include "math/transform.h"
#include "shapes/sphere.h"
#include "world/world.h"
#include "light/lambertian_material.h"
#include "light/gradient_background.h"

SOL_BASE_CLASSES(Sphere, Shape);
SOL_DERIVED_CLASSES(Shape, Sphere);

SOL_BASE_CLASSES(LambertianMaterial, Material);
SOL_DERIVED_CLASSES(Material, LambertianMaterial);

SOL_BASE_CLASSES(GradientBackground, Background);
SOL_DERIVED_CLASSES(Background, GradientBackground);

Scripting::Scripting() {
    initialize_lua();
}

void Scripting::initialize_lua() {
    _lua = std::make_unique<sol::state>();

    // Add standard Lua libraries
    _lua->open_libraries(sol::lib::base);
    _lua->open_libraries(sol::lib::math);

    // Add basic raytracer math types
    _lua->new_usertype<Tuple>("Tuple",
                             sol::constructors<Tuple(), Tuple(float, float, float, float)>());
    _lua->new_usertype<Matrix>("Matrix",
                             sol::constructors<Matrix(int)>());
    _lua->new_usertype<Color>("Color",
        sol::constructors<Color(), Color(float, float, float)>());

    // Add world type
    _lua->new_usertype<World>("World",
                              sol::constructors<World()>(),
                              "objects", &World::objects,
                              "background", &World::background);

    // Add camera type with transform get/set
    sol::usertype<Camera> camera_type = _lua->new_usertype<Camera>("Camera",
                                                                  sol::constructors<Camera(int, int, float)>());
    auto camera_get = static_cast<Matrix(Camera::*)() const>(&Camera::transform);
    auto camera_set = static_cast<void(Camera::*)(const Matrix&)>(&Camera::transform);
    camera_type["transform"] = sol::property(camera_get, camera_set);

    // Add transformation matrix generators
    _lua->set_function("translation", &translation);
    _lua->set_function("scaling", &scaling);
    _lua->set_function("rotation_x", &rotation_x);
    _lua->set_function("rotation_y", &rotation_y);
    _lua->set_function("rotation_z", &rotation_z);
    _lua->set_function("shearing", &shearing);
    _lua->set_function("view_transform", &view_transform);

    // Add shape supertype with transform get/set
    sol::usertype<Shape> shape_type = _lua->new_usertype<Shape>("Shape",
        sol::no_constructor,
        "material", &Shape::material);
    auto shape_get = static_cast<Matrix(Shape::*)() const>(&Shape::transform);
    auto shape_set = static_cast<void(Shape::*)(const Matrix&)>(&Shape::transform);
    shape_type["transform"] = sol::property(shape_get, shape_set);

    // Add Sphere base type
    _lua->new_usertype<Sphere>("Sphere"),
        sol::base_classes, sol::bases<Shape>();
    _lua->set_function("make_sphere", sol::overload(
            []{ return std::make_shared<Sphere>(); },
            [](const Matrix& transform){ return std::make_shared<Sphere>(transform); }));

    // Add material supertype
    _lua->new_usertype<Material>("Material",
                                 sol::no_constructor);

    // Add Lambertian material type
    _lua->new_usertype<LambertianMaterial>("LambertianMaterial",
        sol::base_classes, sol::bases<Material>());
    _lua->set_function("make_lambertian", [](const Color& color){ return std::make_shared<LambertianMaterial>(color); });

    // Add Background supertype
    _lua->new_usertype<Background>("Background",
                                 sol::no_constructor);

    // Add gradient background type
    _lua->new_usertype<GradientBackground>("GradientBackground",
                                           sol::base_classes, sol::bases<Background>());
    _lua->set_function("make_gradient_background", [](const Color& start, const Color& end){ return std::make_shared<GradientBackground>(start, end); });
}

std::pair<World, Camera> Scripting::run_script(const std::string& script) {
    // Clear previous results, and run the script
    _lua->stack_clear();
    _lua->script(script);

    // Get the results of running the script
    World world = _lua->get<World>("world");
    Camera camera = _lua->get<Camera>("camera");

    return {world, camera};
}
