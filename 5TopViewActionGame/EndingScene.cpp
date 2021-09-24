#include "DXUT.h"
#include "CutScene.h"
#include "SceneManager.h"
#include "Font.h"
#include "EndingScene.h"

void EndingScene::Init()
{
	// 한장에 자막
	// Fadein / FadeOut
	for (int i = 0; i < 6; ++i)
	{
		cutscene[i] = new CutScene;
		auto route = L"ending (" + std::to_wstring(i + 1) + L").png";
		cutscene[i]->color = D3DCOLOR_RGBA(0, 0, 0, 255);
		cutscene[i]->SetTexture(route);
		cutscene[i]->position = { screenwidth / 2, screenheight / 2 };
		cutscene[i]->isactive = false;
		cutscene[i]->font->position = { screenwidth / 2, 500 };
		cutscene[i]->font->isactive = false;
	}

	cutscene[0]->isactive = true;
	cutscene[0]->font->isactive = true;
	cutsceneFunc = cutscene[0]->start;

	cutscene[0]->font->SetText("기사가 용을 주겻다");
	cutscene[1]->font->SetText("우와! 용이 주것다");
	cutscene[2]->font->SetText("용이 화내며 저주햇다");
	cutscene[3]->font->SetText("짠 햇다");
	cutscene[4]->font->SetText("뭔가 이상하지 않아? 총잡이가 말했다.\n 하지만 듣는 사람은 아무도 업엇다");
	cutscene[5]->font->SetText("총잡이의 느낌이 맞았따. 저주가 몰려오기 시작한다.");
}

void EndingScene::Update()
{
	if (cutsceneFunc())
	{
		if (isStart == true)
		{
			isStart = false; // 끝나는 효과 나올 차례
			cutsceneFunc = cutscene[cutsceneindex]->end;
		}
		else
		{
			isStart = true;
			cutscene[cutsceneindex]->isactive = false;
			cutscene[cutsceneindex]->font->isactive = false;
			++cutsceneindex;
			if (cutsceneindex == 6)
			{
				SceneManager::GetInstance().ChangeScene(L"Rank");
				return;
			}
			cutsceneFunc = cutscene[cutsceneindex]->start;
			cutscene[cutsceneindex]->isactive = true;
			cutscene[cutsceneindex]->font->isactive = true;
		}
	}
	if (DXUTWasKeyPressed('S'))
		SceneManager::GetInstance().ChangeScene(L"Rank");
}

void EndingScene::Exit()
{
	for (int i = 0; i < 6; ++i)
		delete cutscene[i];
}
