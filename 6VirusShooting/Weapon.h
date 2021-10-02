#pragma once

struct ReturnData
{ 
	std::vector<Vec2> dirs;
	Sprite* sp = nullptr;
};

struct Weapon
{
	// �����ð�
	float reloadtime = 5.f;
	// ��� �߰� �ð� (delay)
	float shootdelay = 0.05f;
	// ���� �Ѿ� ����
	int currentBullet = 0;

	bool autoReload = false;

	// ���
	virtual void Shoot(Vec2 pos) PURE;
	virtual ReturnData CheckShoot(Vec2 pos, Weapon* thisw);
};

struct MachineGun : public Weapon
{
	float focustime = 0.f;
	MachineGun();
	void Shoot(Vec2 pos) override;
};

struct NavalGun : public Weapon
{
	NavalGun();
	void Shoot(Vec2 pos) override;
};

struct TorpedoLauncher : public Weapon
{
	TorpedoLauncher();
	void Shoot(Vec2 pos) override;
};

struct MissileLauncher : public Weapon
{
	MissileLauncher();
	void Shoot(Vec2 pos) override;
};