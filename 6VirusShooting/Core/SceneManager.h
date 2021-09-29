#pragma once
#include "Singleton.h"
#include "RenderManager.h"
#include "Camera.h"
#include "Scene.h"

#define SM SceneManager::GetInstance().

class SceneManager final :
    public Singleton<SceneManager>
{
private:
    std::map<std::wstring, Scene*> sceneMap;
    Scene* currentScene = nullptr;

public:
    bool deviceEnd = false;

    __forceinline void 
        AddScene(const std::wstring& sceneName, Scene* scene) 
    {
        if (sceneMap.find(sceneName) == sceneMap.end())
        {
            sceneMap.emplace(sceneName, scene);
        }
    };

    __forceinline void 
        ChangeScene(const std::wstring& sceneName) 
    {
        Time::timescale = 1.f;
        if (currentScene != nullptr)
            currentScene->Exit();

        RenderManager::GetInstance().ClearAll();

        currentScene = sceneMap[sceneName];
        currentScene->Init();
    };
    
    void UpdateScene() 
    {
        if (currentScene != nullptr)
            currentScene->Update();

        Camera& cam = Camera::GetInstance();
        cam.Update();
    };

    __forceinline void 
        ClearScenes() 
    {
        if (currentScene != nullptr)
            currentScene->Exit();

        for (auto& iter : sceneMap)
        {
            delete iter.second;
        }
        sceneMap.clear();
    };
};

