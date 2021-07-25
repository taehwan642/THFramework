#pragma once
#include "Sprite.h"
#include "Singleton.h"

enum class BlockType
{
	NONE,
	FLOOR,
	OBSTICLE,
	PLAYER,
	OCTOPUS
};

struct Block
{
	BlockType type;
	Sprite* sprite;
};

#define Row 6
#define Column 20

class TileMapManager final :
	public Singleton<TileMapManager>
{
private:
	std::vector<Block> blocks;

	Sprite* blockss[Row][Column];
	BlockType blockTypes[Row][Column];
	
	float blockScale;

	BlockType currentBlocktype;

public:
	Vec2 playerPos;
	std::vector<Vec2> enemyPos;

	TileMapManager();

	void Initialize();

	void UpdateManager();

	[[nodiscard]] __forceinline std::vector<Block>& GetBlockVector()
	{
		return blocks;
	};

	void SaveBlocks();
	void LoadBlocks();

	void ChangeBlocks();

	void DeleteBlocks();
};