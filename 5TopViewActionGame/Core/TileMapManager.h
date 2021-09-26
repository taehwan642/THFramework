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
	MONSTER3, // ���Ÿ� �ذ�
	MONSTER4,
	BOSS1, // �� �ʷ� ����
	BOSS2
};

// Ű�� �ִ� ��� 2��
// 1. ��忡 ���� Ű�� �ٲ��.
// 2. �׳� �� �����ڴ´�.

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

// �� Ŭ������ ����?
// Ÿ�Ͽ� ���õ� �͵�.
// ���⿡�� �÷��̾ �����Ұų�
// �ƴϸ� ������ �÷��̾ �����ϰ� �ΰ�
// �÷��̾��� ��ġ�� �Ѱ��ٰǰ�.
class TileMapManager final :
	public Singleton<TileMapManager>
{
public:
	int count = 0;

	std::vector<BlockType> walls;

	// ���� ���� ���ӿ��� �������ǰ��ִ� ���
	std::vector<Block*> tileBlocks;
	std::vector<Block*> objBlocks; // ������Ʈ

	// Ÿ�ϸ� ���� �� ������ ���
	Block* blocks[Row][Column];
	Block* objects[Row][Column];
	

	BlockType currentBlocktype;

	int mode = 0; // 0 = Ÿ�ϸ�, 1 = ������Ʈ��

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