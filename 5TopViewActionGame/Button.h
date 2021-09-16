#pragma once
#include "Sprite.h"
class Button : public Sprite
{
public:
	std::function<void(void)> function;

	void Update() override;
};

