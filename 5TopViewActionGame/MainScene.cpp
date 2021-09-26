#include "DXUT.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Button.h"
#include "RankScene.h"
#include "Font.h"
#include "RenderManager.h"
#include "MainScene.h"

void MainScene::HelpActive(bool b)
{
	helpBack->isactive = b;
	helpExitButton->isactive = b;
	for (int i = 0; i < 4; ++i)
	{
		helpfont[i]->isactive = b;
		helpui[i]->isactive = b;
	}
}

void MainScene::Init()
{
	background = new Sprite;
	background->isUI = true;
	background->SetTexture(L"background.png");
	background->position = { screenwidth / 2, screenheight / 2 };

	Testbutton = new Button;
	Testbutton->isUI = true;
	Testbutton->SetTexture(L"Start.png");
	Testbutton->position = { screenwidth / 2, screenheight / 2 };

	Testbutton->function = []() {
		SceneManager::GetInstance().ChangeScene(L"Stage1");
	};

	rankButton = new Button;
	rankButton->isUI = true;
	rankButton->SetTexture(L"Ranking.png");
	rankButton->position = { screenwidth / 2 - 400, screenheight / 2 };
	rankButton->function = []()
	{
		RankScene::isCleared = false;
		SceneManager::GetInstance().ChangeScene(L"Rank");
	};

	optionButton = new Button;
	optionButton->isUI = true;
	optionButton->SetTexture(L"mhpbar.png");
	optionButton->position = { screenwidth / 2 + 400, screenheight / 2 };
	optionButton->scale = { 1, 3 };
	optionButton->function = []()
	{
		SceneManager::GetInstance().ChangeScene(L"Option");
	};

	optionFont = new Font(4, 2, L"FuturaBlack BT");

	optionFont->Adapt(optionButton->position,
		const_cast<Texture*>(optionButton->GetTexture()),
		optionButton->scale,
		Vec2(30.f, 30.f));
	optionFont->SetText("설정");

	helpBack = new Sprite;
	helpBack->SetTexture(L"background.png");
	helpBack->color = D3DCOLOR_RGBA(0, 0, 0, 150);
	helpBack->layer = 100;
	helpBack->position = { screenwidth / 2, screenheight / 2 };
	helpBack->isactive = false;
	helpBack->isUI = true;

	helpButton = new Button;
	helpButton->isUI = true;
	helpButton->SetTexture(L"Help.png");
	helpButton->position = { screenwidth / 2 + 400, screenheight / 2 - 200 };
	helpButton->function = [&]()
	{
		helpButton->isactive = false;
		Testbutton->isactive = false;
		rankButton->isactive = false;
		optionButton->isactive = false;
		exitButton->isactive = false;
		optionFont->isactive = false;
		isHelpON = !isHelpON;
		HelpActive(isHelpON);
	};

	helpExitButton = new Button;
	helpExitButton->isUI = true;
	helpExitButton->layer = 101;
	helpExitButton->SetTexture(L"Exit.png");
	helpExitButton->position = { screenwidth / 2, screenheight / 2 + 200 };
	helpExitButton->function = [&]()
	{
		isHelpON = !isHelpON;
		HelpActive(isHelpON);
		helpButton->isactive = true;
		Testbutton->isactive = true;
		rankButton->isactive = true;
		optionButton->isactive = true;
		optionFont->isactive = true;
		exitButton->isactive = true;
	};
	helpExitButton->isactive = false;

	for (int i = 0; i < 4; ++i)
	{
		helpui[i] = new Sprite;
		helpui[i]->layer = 102;
		helpui[i]->scale = { 0.5, 0.5 };
		helpui[i]->SetTexture(L"box.png");
		helpui[i]->isUI = true;
		helpfont[i] = new Font(2, 1, L"Arial");
		helpfont[i]->layer = 103;
		helpfont[i]->SetText("asdf");
		helpui[i]->isactive = false;
		helpfont[i]->isactive = false;
	}

	RenderManager::GetInstance().Sort();

	helpui[0]->position = { 100, 200 };
	helpfont[0]->position = { 150, 150 };
	helpui[1]->position = { 600,200 };
	helpfont[1]->position = { 650,150 };
	helpui[2]->position = { 100,400 };
	helpfont[2]->position = { 150,350 };
	helpui[3]->position = { 600,400 };
	helpfont[3]->position = { 650,350 };

	help.push_back({ L"player (1).png", "플레이어입니다.\n총을 소지하고 있습니다." });
	help.push_back({ L"m1att (1).png", "해골 몬스터입니다.\n원한을 품고 있습니다." });
	help.push_back({ L"door4.png", "문 입니다. 닿는다면\n다음 스테이지로\n넘어갈 수 있습니다." });
	help.push_back({ L"chest (1).png", "상자 입니다.\n파괴하면 아이템이 나옵니다." });
	help.push_back({ L"Hpitem.png", "힐 아이템입니다.\n먹으면 힐이 되며 맛있습니다." });
	help.push_back({ L"Bomb.png", "폭탄입니다.\n피해!" });

	exitButton = new Button;
	exitButton->isUI = true;
	exitButton->layer = 101;
	exitButton->SetTexture(L"Exit.png");
	exitButton->position = { screenwidth / 2, screenheight / 2 - 300 };
	exitButton->function = [&]()
	{
		SceneManager::GetInstance().deviceEnd = true;
		exit(1);
	};
}

void MainScene::Update()
{

	for (int i = 0; i < 4; ++i)
	{
		helpui[i]->SetTexture(L"box.png");
		helpfont[i]->SetText("");
	}

	for (int i = 0; i < 4; ++i)
	{
		if (index + i >= help.size())
			break;

		helpui[i]->SetTexture(help[index + i].textag);
		helpfont[i]->SetText((char*)help[index + i].text.c_str());
	}

	if (DXUTWasKeyPressed(VK_LEFT))
		if (index > 0)
			index -= 4;

	if (DXUTWasKeyPressed(VK_RIGHT))
		if (index + 4 < help.size())
			index += 4;

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);
	if (DXUTIsMouseButtonDown(0))
	{
		if (Testbutton->isactive == true)
			if (PtInRect(&Testbutton->GetRect(), p))
			{
				Testbutton->function();
				return;
			}

		if (rankButton->isactive == true)
			if (PtInRect(&rankButton->GetRect(), p))
			{
				rankButton->function();
				return;
			}

		if (optionButton->isactive == true)
			if (PtInRect(&optionButton->GetRect(), p))
			{
				optionButton->function();
				return;
			}

		if (helpButton->isactive == true)
			if (PtInRect(&helpButton->GetRect(), p))
			{
				helpButton->function();
				return;
			}

		if (helpExitButton->isactive == true)
			if (PtInRect(&helpExitButton->GetRect(), p))
			{
				helpExitButton->function();
				return;
			}

		if (exitButton->isactive == true)
			if (PtInRect(&exitButton->GetRect(), p))
			{
				exitButton->function();
				return;
			}
	}
}

void MainScene::Exit()
{
	delete background;
	delete Testbutton;
	delete rankButton;
	delete optionButton;
	delete optionFont;
	delete helpBack;
	help.clear();
	delete helpButton;
	delete helpExitButton;
	delete exitButton;
	for (int i = 0; i < 4; ++i)
	{
		delete helpui[i];
		delete helpfont[i];
	}
}