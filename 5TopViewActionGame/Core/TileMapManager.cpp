#include "DXUT.h"
#include "Camera.h"
#include "TileMapManager.h"

TileMapManager::TileMapManager() : blockScale(0.5f), currentBlocktype(BlockType::FLOOR)
{
	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			blockss[i][j] = nullptr;
		}
	}
}

void 
TileMapManager::Initialize()
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			blockss[i][j] = new Block;
			blockss[i][j]->SetTexture(L"box.png");
			blockss[i][j]->scale = { blockScale, blockScale };

			const Texture* t = blockss[i][j]->GetTexture();

			if (x > (std::size(blockss[i]) - 1))
			{
				x = 0;
				++y;
			}

			blockss[i][j]->SetPosition(
				((blockss[i][j]->scale.x * t->info.Width) / 2) + (x * t->info.Width * blockss[i][j]->scale.x),
				((blockss[i][j]->scale.y * t->info.Height) / 2) + (y * t->info.Height * blockss[i][j]->scale.y));

			++x;

			blockss[i][j]->type = BlockType::NONE;
		}
	}
}

void
TileMapManager::UpdateManager()
{
	ChangeBlocks();
	POINT pnt;
	GetCursorPos(&pnt);
	ScreenToClient(DXUTGetHWND(), &pnt);

	Camera& cam = Camera::GetInstance();
	Vec2 camPos = cam.GetPosition();
	pnt.x = (camPos.x - screenwidth / 2) + pnt.x;
	pnt.y = (camPos.y - screenheight / 2) + pnt.y;

	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{

			if (PtInRect(&blockss[i][j]->GetRect(), pnt))
			{
				if (DXUTIsKeyDown(VK_SPACE))
				{
					blockss[i][j]->type = currentBlocktype;
				}
			}

			switch (blockss[i][j]->type)
			{
			case BlockType::NONE: 
			{
				blockss[i][j]->SetTexture(L"box.png");
				break; 
			}
			
			case BlockType::FLOOR: 
			{
				blockss[i][j]->SetTexture(L"block.png");
				break; 
			}
			
			case BlockType::OBSTICLE: 
			{
				break; 
			}
			
			default:
				break;
			}
		}
	}
}

void
TileMapManager::SaveBlocks(const std::string& mapTag)
{
	// 외부에 출력하기 위해서 파일 생성 또는 받아오기
	// 만약 열 파일이 없다면 생성
	// output file stream
	std::ofstream oin(mapTag);

	// blockss의 사이즈는? blockss[ 이 부분 ][]
	for (int i = 0; i < std::size(blockss); ++i)
	{
		// blockss[] 의 사이즈는? blockss[][ 이 부분 ]
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			// typeValue의 의미? blockss 속에 있던 type(enum) 을 int로 변환한 값
			int typeValue = (BlockType)blockss[i][j]->type;
			// 그걸 넣어준다.
			oin << typeValue;
			// 왜 타입만 넣어주고 위치, 사이즈는 안넣어주는가?
			// 위치는 빈 공간은 0으로 설정되기 때문에 위치값은 일정하게 찍힌다.
			// 사이즈는 "고정" 이기 때문
		}
	}

	oin.close();
}

void
TileMapManager::LoadBlocks(const std::string& mapTag)
{
	for (auto& iter : blocks)
		delete iter;
	blocks.clear();

	// input file stream
	// 파일을 열어서 정보를 받는다.
	// 이 때 열지 못한다면 fail()함수가 true를 리턴.
	std::ifstream fin(mapTag);
	if (fin.fail())
	{
		std::cout << "파일이 없습니다." << std::endl;
		return;
	}
	char typeValue;
	int x = 0;
	int y = 0;
	// 파일 내부를 순환하며 얻어온 "문자" 값을 typeValue에 넣어줌.
	// 예를 들어 파일 안에 "01010" 라는 글이 있다면
	// get으로 받아올 때 
	// 0
	// 1
	// 0
	// 1
	// 0
	// 이렇게 불러옴. 한번에 한번 while돌면서.
	// 그리고 get함수가 true가 나오면 파일이 아직 안끝났다는 뜻.
	// while(true)면 계속 도는것과 같은 이치.
	// 그래서 계속 돕니다
	// 근데 false가 나왔따? 그럼 EOF. (End-Of-File)
	// 파일의 끝에 닿아서 더 이상 읽을 게 없다는 뜻.
	while (fin.get(typeValue)) 
	{
		// atoi == char to int
		int chartoint = atoi(&typeValue);
		BlockType type = (BlockType)chartoint;

		if (x > (std::size(blockss[0]) - 1))
		{
			x = 0;
			++y;
		}

		if (type == BlockType::NONE )
		{
			++x;
			continue;
		}

		Block* block;
		block = new Block();
		block->type = type;
		block->scale = { blockScale, blockScale };

		switch (type)
		{
		case BlockType::NONE:
			block->SetTexture(L"box.png");
			break;
		case BlockType::FLOOR:
			block->SetTexture(L"block.png");
			break;
		case BlockType::OBSTICLE:
			block->SetTexture(L"block2.png");
			break;
		default:
			break;
		}

		const Texture* t = block->GetTexture();

		block->SetPosition(
			((block->scale.x * t->info.Width) / 2) + (x * t->info.Width * block->scale.x),
			((block->scale.y * t->info.Height) / 2) + (y * t->info.Height * block->scale.y));

		blocks.push_back(block);

		++x;
	}

	fin.close();
}

void TileMapManager::ChangeBlocks()
{
	if (DXUTWasKeyPressed(VK_F1))
	{
		currentBlocktype = BlockType::FLOOR;
	}
}

void 
TileMapManager::DeleteBlocks()
{
	if (blockss[0] != nullptr)
	{
		for (int i = 0; i < std::size(blockss); ++i)
		{
			for (int j = 0; j < std::size(blockss[i]); ++j)
			{
				delete blockss[i][j];
			}
		}
	}

	for (auto& iter : blocks)
	{
		delete iter;
	}
	blocks.clear();
}
