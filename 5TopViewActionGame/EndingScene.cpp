#include "DXUT.h"
#include "CutScene.h"
#include "SceneManager.h"
#include "Font.h"
#include "EndingScene.h"

void EndingScene::Init()
{
	// ���忡 �ڸ�
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

	cutscene[0]->font->SetText("��簡 ���� �ְ��");
	cutscene[1]->font->SetText("���! ���� �ְʹ�");
	cutscene[2]->font->SetText("���� ȭ���� �����޴�");
	cutscene[3]->font->SetText("§ �޴�");
	cutscene[4]->font->SetText("���� �̻����� �ʾ�? �����̰� ���ߴ�.\n ������ ��� ����� �ƹ��� ������");
	cutscene[5]->font->SetText("�������� ������ �¾ҵ�. ���ְ� �������� �����Ѵ�.");
}

void EndingScene::Update()
{
	if (cutsceneFunc())
	{
		if (isStart == true)
		{
			isStart = false; // ������ ȿ�� ���� ����
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
