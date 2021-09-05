#pragma once
#include "Object.h"

class Font : public Object
{
public:
	LPD3DXFONT font;
	char buffer[256];

	Font(float scale, float weight, LPCWSTR path);
	virtual ~Font();

	void SetText(char* text);

	void Render() override;
};

