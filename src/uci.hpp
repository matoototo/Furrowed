#pragma once

#include "engine.hpp"

struct UCI {
    UCI(Engine& engine) : engine(engine) {}

    void run();
    void go(std::istringstream& is);
    void position(std::istringstream& is);

    Engine& engine;
};
