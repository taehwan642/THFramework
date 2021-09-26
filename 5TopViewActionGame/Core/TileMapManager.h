#pragma once
#include "Sprite.h"
#include "Singleton.h"

enum BlockType
{
	NONE,
	FLOOR,
	WALL1,
	WALL2,
	WALL3,
	WALL4,
	CORNER1,
	CORNER2,
	CORNER3,
	CORNER4,

	DOOR1,
	DOOR2,
	DOOR3,
	DOOR4,
	WINDOW1,
	WINDOW2,
	CHEST,
	PLAYER,
	MONSTER1,
	MONSTERSPAWNER,
	MONSTER2,
	MONSTER3, // 원거리 해골
	MONSTER4,
	BOSS1, // 그 초록 대포
	BOSS2
};

// 키를 넣는 방법 2개
// 1. 모드에 따라서 키가 바뀐다.
// 2. 그냥 다 때려박는다.

class Block final : 
	public Sprite
{
public:
	BlockType type;
	void Update() override {};
};

struct MonsterTag
{
	BlockType type;
	Vec2 position;
};

struct DoorTag
{
	Vec2 pos;
	BlockType doortype;
};

#define Row 6
#define Column 20

// 이 클래스의 목적?
// 타일에 관련된 것들.
// 여기에서 플레이어를 생성할거냐
// 아니면 씬에서 플레이어를 생성하게 두고
// 플레이어의 위치를 넘겨줄건가.
class TileMapManager final :
	public Singleton<TileMapManager>
{
public:
	int count = 0;

	std::vector<BlockType> walls;

	// 현재 실제 게임에서 렌더링되고있는 블록
	std::vector<Block*> tileBlocks;
	std::vector<Block*> objBlocks; // 오브젝트

	// 타일맵 찍을 때 렌더할 블록
	Block* blocks[Row][Column];
	Block* objects[Row][Column];
	

	BlockType currentBlocktype;

	int mode = 0; // 0 = 타일맵, 1 = 오브젝트맵

	float blockScale;

	Vec2 playerpos;
	std::vector<Vec2> chestpos;
	std::vector<MonsterTag> monsterpos;
	DoorTag doortag;

	TileMapManager();

	void Initialize();

	void UpdateManager();

	std::wstring GetTextureTag(BlockType type);

	[[nodiscard]] __forceinline std::vector<Block*>& GetBlockVector()
	{
		return tileBlocks;
	};

	void SaveBlocks(const std::string& mapTag);
	void SaveObject(const std::string& mapTag);
	void LoadBlocks(const std::string& mapTag);
	void LoadObject(const std::string& mapTag);

	void UpdateBlocks(const std::string& mapTag);
	void UpdateObject(const std::string& mapTag);

	void ChangeBlocks();

	void DeleteBlocks();
};