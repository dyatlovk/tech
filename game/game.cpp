#include "app.hpp"
#include <Engine/Engine.hpp>
#include <memory>

int main(int argc, char **argv)
{
    using namespace mtEngine;
    using namespace Game;
    auto engine = std::make_unique<Engine>(argv[0]);
    engine->SetApp(std::make_unique<GameApp>());
    auto exitCode = engine->Run();
    return exitCode;
}
