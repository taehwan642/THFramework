#include "DXUT.h"
#include "Font.h"
#include "Sprite.h"
#include "Button.h"
#include "SceneManager.h"
#include "RankScene.h"

std::vector<RankData> RankScene::datas = {};
int RankScene::score = 0;
bool RankScene::isCleared = false;

void RankScene::Init()
{
	back = new Sprite;
	back->isUI = true;
	back->position = { screenwidth / 2, screenheight / 2 };
	back->layer = -1;
	back->SetTexture(L"ScoreBoard.png");

	name[0] = ' ';
	name[1] = ' ';
	name[2] = ' ';
	name[3] = '\0';

	for (int i = 0; i < 5; ++i)
	{
		fonts[i] = new Font(4, 1, L"Arial");
		fonts[i]->isUI = true;
		fonts[i]->position = { screenwidth / 2 + 200,
			screenheight / 2 - 300 + ((float)i * 80) };
		fonts[i]->SetText("empty");
	}

	nameFont = new Font(4, 1, L"Arial");
	nameFont->isUI = true;
	nameFont->position = { screenwidth / 2 - 500,
		screenheight / 2 - 100
	};
	nameFont->SetText("asdf");

	scoreFont = new Font(4, 1, L"Arial");
	scoreFont->isUI = true;
	scoreFont->position = { screenwidth / 2 - 500,
		screenheight / 2 - 20
	};
	scoreFont->SetText("asdf");

	returnButton = new Button;
	returnButton->isUI = true;
	returnButton->SetTexture(L"Exit.png");
	returnButton->position = {
		screenwidth / 2 - 500,
		screenheight / 2 + 300
	};
	returnButton->function = []() {
		SceneManager::GetInstance().ChangeScene(L"Main");
	};

	isEntered = false;
}

void RankScene::Update()
{
	// 알파벳 개수, 'A' 부터 26개.
	if (isCleared == true)
	{
		if (isEntered == false)
		{
			for (int i = 0; i < 26; ++i)
			{
				if (DXUTWasKeyPressed('A' + i))
				{
					for (int j = 0; j < 3; ++j)
					{
						if (name[j] == ' ')
						{
							name[j] = 'A' + i;
							break;
						}
					}
				}
			}
		}
	}


	if (DXUTWasKeyPressed(VK_BACK))
	{
		for (int j = 0; j < 3; ++j)
		{
			name[j]  = ' ';
		}
	}

	if (isCleared == true)
	{
		if (isEntered == false)
		{
			if (DXUTWasKeyPressed(VK_RETURN))
			{
				RankData data;

				for (int j = 0; j < 3; ++j)
					data.name[j] = name[j];

				data.score = score;
				datas.push_back(data);
				std::sort(datas.begin(), datas.end(),
					[](RankData a, RankData b)
					{return a.score > b.score; }
				); // 3, 2, 1,0

				isEntered = true;
			}
		}
	}
	
	for (int i = 0; i < 5; ++i)
	{
		if (i >= datas.size())
			break;

		std::string s{};
		// 이름 : 스코어
		for (int j = 0; j < 3; ++j)
			s += datas[i].name[j];
		s += " : ";
		s += std::to_string(datas[i].score);
		fonts[i]->SetText((char*)s.c_str());
	}


	nameFont->SetText(name);
	// to_string으로 int->string으로 변환. 
	// string으로 변환이 됐을 때 그거의 c_str의 리턴값은 const char*
	// char*타입으로 들어가야함. 그러니까 타입 (char*)로 변환.
	scoreFont->SetText((char*)std::to_string(score).c_str());

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);

	if (DXUTIsMouseButtonDown(0))
	{
		if (isCleared == true && isEntered == true)
		{
			if (PtInRect(&returnButton->GetRect(), p))
			{
				returnButton->function();
				return;
			}
		}

		if (isCleared == false)
		{
			if (PtInRect(&returnButton->GetRect(), p))
			{
				returnButton->function();
				return;
			}
		}
	}
}

void RankScene::Exit()
{
	delete back;
	for (int i = 0; i < 5; ++i)
	{
		delete fonts[i];
	}
	delete nameFont;
	delete scoreFont;
	delete returnButton;
}
