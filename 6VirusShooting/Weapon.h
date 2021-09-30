#pragma once
struct Weapon
{
	// 장전시간
	float reloadtime = 5.f;
	// 쏘는 중간 시간 (delay)
	float shootdelay = 0.05f;
	// 현재 총알 개수
	int currentBullet = 0;

	bool autoReload = false;

	// 쏘기
	virtual void Shoot(Vec2 pos) PURE;
	virtual std::vector<Vec2> CheckShoot(Vec2 pos);
};

struct MachineGun : public Weapon
{
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