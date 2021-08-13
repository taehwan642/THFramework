#include "DXUT.h"
#include "PlayerLVupUI.h"

PlayerLVupUI::PlayerLVupUI()
{
	for (int i = 0; i < std::size(statupUI); ++i)
	{
		statupUI[i] = new StatUpUI;
		statupUI[i]->isactive = false;
	}
}

void PlayerLVupUI::Update()
{
	for (int i = 0; i < std::size(statupUI); ++i)
	{
		if (DXUTIsMouseButtonDown(VK_LEFT))
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(DXUTGetHWND(), &pt);
			if (PtInRect(&statupUI[i]->GetRect(), pt))
			{
				statupUI[i]->statup;
					return;
			}
		}
	}
}

void PlayerLVupUI::ShowUI()
{
		
	for (int i = 0; i < std::size(statupUI); ++i)
	{
		statupUI[i]->isactive = true;
	}
}
