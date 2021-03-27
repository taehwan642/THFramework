#include "DXUT.h"
#include "Director.h"
#include "RankingScene.h"

void RankingScene::Init()
{
	name[0] = ' ';
	name[1] = ' ';
	name[2] = ' ';
	name[3] = '\0';
	
	for (int i = 0; i < 5; ++i)
	{
		fonts[i] = new Font();
		fonts[i]->Createfont(2, 1, L"Arial");
		fonts[i]->SetFont("");
		fonts[i]->position = { 800, 100 + (float)i * 100 };
	}

	nameFont = new Font();
	nameFont->Createfont(2, 1, L"Arial");
	nameFont->SetFont("");
	nameFont->position = { 50,100 };

	scoreFont = new Font();
	scoreFont->Createfont(2, 1, L"Arial");
	scoreFont->SetFont("");
	scoreFont->position = { 50,200 };

	returnFont = new Font();
	returnFont->Createfont(2, 1, L"Arial");
	returnFont->SetFont("Press P to return");
	returnFont->position = { 800,600 };
	Director::GetInstance()->isgameend == false ? isentered = true : isentered = false;
}

void RankingScene::Update()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);
	if (isentered == false && Director::GetInstance()->isgameend == true)
	{
		for (int i = 0; i < 26; ++i)
		{
			if (DXUTWasKeyPressed('A' + i))
			{
				for (int j = 0; j < 4; ++j)
				{
					if (name[j] == ' ')
					{
						name[j] = 'A' + i;
						break;
					}
				}
			}
		}

		char buff[256] = { 0, };
		sprintf(buff, "INITIAL : %s", name);
		nameFont->SetFont(buff);
		sprintf(buff, "SCORE : %d", Director::GetInstance()->latestScore);
		scoreFont->SetFont(buff);

	}
	
	if (DXUTWasKeyPressed(VK_BACK))
	{
		name[0] = ' ';
		name[1] = ' ';
		name[2] = ' ';
		name[3] = '\0';
	}

	if (DXUTWasKeyPressed(VK_RETURN))
	{
		if (name[0] != ' ' &&
			name[1] != ' ' &&
			name[2] != ' ')
		{
			Rank r;
			for (int i = 0; i < 3; ++i)
				r.name[i] = name[i];
			r.name[3] = '\0';
			r.score = Director::GetInstance()->latestScore;
			Director::GetInstance()->ranking.emplace_back(r);
			sort(Director::GetInstance()->ranking.begin(), 
				Director::GetInstance()->ranking.end(), 
				Director::GetInstance()->Comp);
			name[0] = ' ';
			name[1] = ' ';
			name[2] = ' ';
			name[3] = '\0';
			nameFont->SetFont("");
			scoreFont->SetFont("");
			isentered = true;
			Director::GetInstance()->isgameend = false;
		}
	}

	for (int i = 0; i < Director::GetInstance()->ranking.size(); ++i)
	{
		if (i < 5)
		{
			char buff[256] = { 0, };
			sprintf(buff, "%d : %s %d", i + 1,
				Director::GetInstance()->ranking[i].name,
				Director::GetInstance()->ranking[i].score);
			fonts[i]->SetFont(buff);
		}
	}


	if (DXUTWasKeyPressed('P') && isentered == true)
	{
		Director::GetInstance()->ChangeScene(MENUSCENE);
		return;
	}
}

void RankingScene::Exit()
{
	for (int i = 0; i < 5; ++i)
		delete fonts[i];
	delete nameFont;
	delete scoreFont;
	delete returnFont;
}
