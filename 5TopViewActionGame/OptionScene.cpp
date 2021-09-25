#include "DXUT.h"
#include "Button.h"
#include "Font.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "OptionScene.h"

void OptionScene::Init()
{
	toggleFull = new Button;
	toggleFull->isUI = true;
	toggleFull->position = { screenwidth / 2 - 200, screenheight / 2 };
	toggleFull->SetTexture(L"mhpbar.png");
	toggleFull->scale = { 1,3 };
	toggleFull->function = [&]() 
	{
		DXUTToggleFullScreen();
	};

	fullfont = new Font(2, 1, L"FuturaBlack BT");

	fullfont->Adapt(toggleFull->position, 
		const_cast<Texture*>(toggleFull->GetTexture()), 
		toggleFull->scale, 
		Vec2(30.f, 30.f));

	fullfont->SetText("Window Mode");

	SoundManager::GetInstance().Play(L"bgm", 0, true);

	soundfont = new Font(2,1, L"FuturaBlack BT");
	soundfont->position = { screenwidth / 2, screenheight / 2 + 100 };
	soundfont->SetText("소리 크기를 높이려면 위 방향키\n줄이려면 아래 방향키를 눌러주세요.\n스페이스바로 소리를 다시 재생할 수 있습니다.");

	exit = new Button;
	exit->isUI = true;
	exit->position = { screenwidth / 2 + 200, screenheight / 2 + 100 };
	exit->SetTexture(L"Exit.png");
	exit->function = [&]()
	{
		SceneManager::GetInstance().ChangeScene(L"Main");
	};
}

void OptionScene::Update()
{
	if (DXUTWasKeyPressed(VK_UP))
		SoundManager::GetInstance().worldVolume += 200;
	if (DXUTWasKeyPressed(VK_DOWN))
		SoundManager::GetInstance().worldVolume -= 200;
	if (DXUTWasKeyPressed(VK_SPACE))
	{
		SoundManager::GetInstance().Stop(L"bgm");
		SoundManager::GetInstance().Play(L"bgm", 0, true);
	}

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);

	DXUTDeviceSettings deviceSettings = DXUTGetDeviceSettings();
	BOOL bIsWindowed = deviceSettings.d3d9.pp.Windowed;
	bIsWindowed ?
		fullfont->SetText("FullScreen Mode") : // true
		fullfont->SetText("Window Mode"); // false
	
	if (DXUTIsMouseButtonDown(0))
	{
		if (PtInRect(&toggleFull->GetRect(), p))
		{
			toggleFull->function();
		}
		if (PtInRect(&exit->GetRect(), p))
		{
			exit->function();
			return;
		}
	}
}

void OptionScene::Exit()
{
	SoundManager::GetInstance().Stop(L"bgm");

	delete fullfont;
	delete toggleFull;
	delete soundfont;
	delete exit;
}