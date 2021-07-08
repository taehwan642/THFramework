#include "DXUT.h"
#include "SceneManager.h"

void SceneManager::AddScene(const std::wstring& sceneName, Scene* scene)
{
	if (sceneMap.find(sceneName) == sceneMap.end())
	{
		sceneMap.emplace(sceneName, scene);
	}
}

void SceneManager::ChangeScene(const std::wstring& sceneName)
{
	if(currentScene != nullptr)
		currentScene->Exit();

	currentScene = sceneMap[sceneName];
	currentScene->Init();
}

void SceneManager::UpdateScene()
{
	if (currentScene != nullptr)
		currentScene->Update();
}

void SceneManager::ClearScenes()
{
	for (auto& iter : sceneMap)
	{
		delete iter.second;
	}
	sceneMap.clear();
}
