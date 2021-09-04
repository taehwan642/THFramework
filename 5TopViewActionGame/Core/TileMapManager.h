#pragma once
#include "Sprite.h"
#include "Singleton.h"

enum class BlockType
{
	NONE,
	FLOOR,
	OBSTICLE,
	PLAYER,
	OCTOPUS,
	DOOR,
	BOSS
};

class Block final : 
	public Sprite
{
public:
	BlockType type;
	void Update() override {};
};

#define Row 6
#define Column 20

class TileMapManager final :
	public Singleton<TileMapManager>
{
private:
	std::vector<Block*> blocks;

	Sprite* blockss[Row][Column];
	BlockType blockTypes[Row][Column];
	
	float blockScale;

	BlockType currentBlocktype;

public:
	Vec2 playerPos;
	std::vector<std::pair<BlockType, Vec2>> enemyPos;
	Vec2 doorPos;

	TileMapManager();

	void Initialize();

	void UpdateManager();

	[[nodiscard]] __forceinline std::vector<Block*>& GetBlockVector()
	{
		return blocks;
	};

	void SaveBlocks(const std::string& mapTag);
	void LoadBlocks(const std::string& mapTag);

	void ChangeBlocks();

	void DeleteBlocks();
};