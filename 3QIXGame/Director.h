#include "Scene.h"
#include "Camera.h"
#include "Singleton.h"
#pragma once
class Director : // 총 관리자. 씬의 이동 변경을 담당합니다.
	public Singleton<Director>
{
private:
	map<SceneTag, Scene*> sceneMap;
	Scene* currentScene; // 현재 다이렉트x에서 돌아가는 씬
public:
	POINT p;
	float timescale = 1;
	int Score = 0;
	int mouse = 0;
	bool OnMouseDown()
	{
		if (mouse == 1)
		{
			return true;
		}
		return false;
	};
	bool OnMouse()
	{
		if (mouse == 2)
		{
			return true;
		}
		return false;
	};
	bool OnMouseUp()
	{
		if (mouse == 3)
		{
			return true;
		}
		return false;
	};
	LPD3DXSPRITE sprite;

	Vec2 GetMousePos()
	{
		GetCursorPos(&p);
		ScreenToClient(DXUTGetHWND(), &p);
		return { float(p.x), float(p.y) };
	};

	std::vector<Rank> ranking;
	static bool Comp(Rank a, Rank b) { return a.score > b.score; };

	int latestScore = 0;
	bool isgameend = false;

	void Init();
	void AddScene(SceneTag _sceneTag, Scene* _scene);
	void ChangeScene(SceneTag _sceneTag);
	void UpdateScene();

	void ReleaseAllScenes();
};
