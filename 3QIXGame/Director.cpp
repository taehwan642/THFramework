#include "DXUT.h"
#include "Renderer.h"
#include "Director.h"

void Director::Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);
}

void Director::AddScene(SceneTag _sceneTag, Scene* _scene)
{
	auto iter = sceneMap.find(_sceneTag);
	if (iter == sceneMap.end())
	{
		sceneMap[_sceneTag] = _scene;
	}
}

void Director::ChangeScene(SceneTag _sceneTag)
{
	if (currentScene != nullptr)
	{
		currentScene->Exit();
	}
	Renderer::GetInstance()->Clear();
	currentScene = sceneMap[_sceneTag];
	currentScene->Init();
}

void Director::UpdateScene()
{
	if (currentScene != nullptr)
	{
		currentScene->Update();
		Renderer::GetInstance()->Render();
	}
}

void Director::ReleaseAllScenes()
{
	currentScene->Exit();
	for (auto it : sceneMap)
	{
		delete it.second;
	}
}
