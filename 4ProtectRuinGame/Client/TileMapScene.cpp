#include "DXUT.h"
#include "SceneManager.h"
#include "Camera.h"
#include "TileMapScene.h"

void 
TileMapScene::Init()
{
	TileMapManager& tmm = TileMapManager::GetInstance();
	tmm.Initialize();

	Camera& cam = Camera::GetInstance();
	cam.Initialize();

	cam.SetCameraSize(1.f);
}

void 
TileMapScene::Update()
{
	TileMapManager& tmm = TileMapManager::GetInstance();
	Camera& cam = Camera::GetInstance();

	Vec2 camPos = cam.GetPosition();

	if (DXUTIsKeyDown(VK_UP))
	{
		camPos.y -= 1000.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown(VK_DOWN))
	{
		camPos.y += 1000.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown(VK_LEFT))
	{
		camPos.x -= 1000.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown(VK_RIGHT))
	{
		camPos.x += 1000.f * DXUTGetElapsedTime();
	}

	cam.SetPosition(camPos);

	tmm.UpdateManager();

	if (DXUTWasKeyPressed('O'))
		tmm.SaveBlocks();

	if (DXUTWasKeyPressed('M'))
		SceneManager::GetInstance().ChangeScene(L"Stage1");
}

void 
TileMapScene::Exit()
{

}
