#include "DXUT.h"
#include "Stage1.h"

void 
Stage1::Init()
{
}

void 
Stage1::Update()
{
	TileMapManager& tmm = TileMapManager::GetInstance();



	if (DXUTWasKeyPressed('P'))
		tmm.LoadBlocks();
}

void 
Stage1::Exit()
{
}
