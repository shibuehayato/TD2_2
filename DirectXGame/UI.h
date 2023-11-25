#pragma once
#include"Sprite.h"
#include"TextureManager.h"
class UI {
public:
	void Initialize();

	void Update();

	void Draw();

private:
	uint32_t texturesUI[6];

Sprite* uisprites_[6];

};
