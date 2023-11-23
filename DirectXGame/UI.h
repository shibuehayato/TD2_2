#pragma once
#include"Sprite.h"
#include"TextureManager.h"
class UI {
public:
	void Initialize();

	void Update();

	void Draw();

private:
	uint32_t textureUI[3];

Sprite* uisprites_[3];

};
