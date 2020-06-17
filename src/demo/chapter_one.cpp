#include "chapter_one.h"
#include <iostream>

Environment::Environment(Tuple gravity, Tuple wind) : gravity(gravity), wind(wind) {}

Projectile::Projectile(Tuple position, Tuple velocity) : position(position), velocity(velocity) {}

void Projectile::tick(Environment env) {
    position = position + velocity;
    velocity = velocity + env.gravity + env.wind;
}

void run_chapter_one() {
    Projectile proj = Projectile(Tuple::point(0, 1, 0), Tuple::vector(1, 1, 0).normalized() * 8);
    Environment env = Environment(Tuple::vector(0, -0.1f, 0), Tuple::vector(-0.01f, 0, 0));

    int ticks = 0;
    while (proj.position.y > 0) {
        std::cout << proj.position << std::endl;
        proj.tick(env);
        ticks++;
    }
    std::cout << ticks << std::endl;
}
