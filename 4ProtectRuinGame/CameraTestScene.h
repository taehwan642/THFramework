#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Sprite.h"
class CameraTestScene :
    public Scene
{
public:
    Sprite* sp;
    void Init() override;
    void Update() override;
    void Exit() override;
};

