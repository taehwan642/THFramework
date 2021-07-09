#include "DXUT.h"
#include "RenderManager.h"

void RenderManager::AddRenderObjects(Object* obj)
{
	renderObjects.emplace_back(obj);
}

void RenderManager::DeleteRender(Object* obj)
{
	renderObjects.emplace_back(obj);
}

void RenderManager::Sort()
{
	renderObjects.sort(Comp);
}

void RenderManager::Render()
{
	for (auto& iter : renderObjects)
	{
		iter->Update();
		iter->Draw();
	}
}
