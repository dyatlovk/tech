#include "Scenes.hpp"

namespace mtEngine
{
  Scenes::Scenes(){};

  void Scenes::Update()
  {
    if (!scene)
      return;

    if (!scene->started)
    {
      scene->Start();
      scene->started = true;
    }

    if (scene->GetCamera())
      scene->GetCamera()->Update();

    scene->BeforeUpdate();
    scene->Update();
    if (scene->GetStructure())
      scene->GetStructure()->Update();
    scene->AfterUpdate();
  }

  void Scenes::Shutdown()
  {
    scene->Shutdown();
    PLOGD << "scenes shutdown";
  }
} // namespace mtEngine
