#pragma once
#include <cstdint>
#include <memory>
#include <Sprite.h>

class GameScene;

class TimeLimit {
public:
	void Initialize();
	void Update();
	void Draw();
	void Reset();

private:
	// テクスチャハンドル
	uint32_t TimeTexture_[15] = {0};
	// スプライト
	std::unique_ptr<Sprite> TimeSprite_[15] = {0};

	int timer_ = 60 * 60;
};