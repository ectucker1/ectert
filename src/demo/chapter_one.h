#pragma once

#include "math/tuple.h"

struct Environment {

public:
    Tuple gravity, wind;

    Environment(Tuple gravity, Tuple wind);

};

struct Projectile {

public:
    Tuple position, velocity;

    Projectile(Tuple position, Tuple velocity);

    void tick(Environment env);

};

void run_chapter_one();
