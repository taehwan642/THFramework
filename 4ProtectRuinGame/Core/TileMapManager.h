#pragma once
#include "Sprite.h"
#include "Singleton.h"

enum class BlockType
{
	NONE,
	FLOOR,
	OBSTICLE
};

struct Block
{
	BlockType type;
	Sprite* sprite;
};

#define Row 6
#define Column 20

class TileMapManager :
	public Singleton<TileMapManager>
{
	// 1. 마우스로 클릭하면 거기에 가장 가까운 자리에 놓아지기
	// 2. 1, 2, 3 등 숫자 누르면 블록 성질 바뀌기
	// 3. 특정 키 누르면 txt파일로 저장
	// 4. 특정 키 누르면 txt파일 불러오기

private:
	std::vector<Block> blocks;

	Sprite* blockss[Row][Column];
	BlockType blockTypes[Row][Column];
	
	float blockScale;
public:
	TileMapManager();

	void Initialize();

	void UpdateManager();

	std::vector<Block>& GetBlockVector();

	void SaveBlocks();
	void LoadBlocks();

	void DeleteBlocks();
};