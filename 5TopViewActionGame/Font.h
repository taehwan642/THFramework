#pragma once
#include "Object.h"
class Texture;

class Font : public Object
{
public:
	LPD3DXFONT font;
	char buffer[256];

	void Adapt(Vec2 pos, Texture* tex, Vec2 sc, Vec2 intv);

	Font(float scale, float weight, LPCWSTR path);
	virtual ~Font();

	void SetText(char* text);

	void Render() override;
};

