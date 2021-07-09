#include "DXUT.h"
#include "RenderManager.h"

void RenderManager::Render()
{
	for (auto& iter : renderObjects)
	{
		iter->Update();
		iter->Render();
	}
}
