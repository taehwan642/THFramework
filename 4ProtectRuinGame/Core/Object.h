#pragma once
class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	Vec2 position = { 0.f, 0.f };
	Vec2 scale = { 0.f, 0.f };
	Vec2 pivot = { 0.5f, 0.5f };

	int layer = 0;

	float rotation = 0.f;

	bool isactive = true;

	Color color = D3DCOLOR_RGBA(255, 255, 255, 255);

	RECT imgRect;

	virtual void Update() {};
	virtual void Draw() {};

	D3DXMATRIX GetMatrix();
};