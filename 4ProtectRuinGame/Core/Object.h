#pragma once
class Object
{
protected:
	Object() = default;

public:
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
	virtual void Render() {};

	[[nodiscard]] __forceinline D3DXMATRIX GetMatrix() const
	{
		D3DXMATRIX result;

		D3DXMatrixTransformation2D(&result, nullptr, 0, &scale, nullptr, rotation, &position);

		return result;
	};
};