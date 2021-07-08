#pragma once
#include "Singleton.h"
#include "Scene.h"
class SceneManager :
    public Singleton<SceneManager>
{
private:
    std::map<std::wstring, Scene*> sceneMap;
    Scene* currentScene = nullptr;

public:
    void AddScene(const std::wstring& sceneName, Scene* scene);
    void ChangeScene(const std::wstring& sceneName);
    void UpdateScene();
    void ClearScenes();
};

