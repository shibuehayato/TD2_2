#include "TimeLimit.h"
#include <TextureManager.h>

void TimeLimit::Initialize() 
{ 
	TimeTexture_[0] = TextureManager::Load("time/Time60.png");
	TimeTexture_[1] = TextureManager::Load("time/Time50.png");
	TimeTexture_[2] = TextureManager::Load("time/Time40.png");
	TimeTexture_[3] = TextureManager::Load("time/Time30.png");
	TimeTexture_[4] = TextureManager::Load("time/Time20.png");
	TimeTexture_[5] = TextureManager::Load("time/Time10.png");
	TimeTexture_[6] = TextureManager::Load("time/Time9.png");
	TimeTexture_[7] = TextureManager::Load("time/Time8.png");
	TimeTexture_[8] = TextureManager::Load("time/Time7.png");
	TimeTexture_[9] = TextureManager::Load("time/Time6.png");
	TimeTexture_[10] = TextureManager::Load("time/Time5.png");
	TimeTexture_[11] = TextureManager::Load("time/Time4.png");
	TimeTexture_[12] = TextureManager::Load("time/Time3.png");
	TimeTexture_[13] = TextureManager::Load("time/Time2.png");
	TimeTexture_[14] = TextureManager::Load("time/Time1.png");
	for (int i = 0; i < 15; i++) {
		TimeSprite_[i] = std::make_unique<Sprite>();
	}
	for (int i = 0; i < 15; i++) {
		TimeSprite_[i].reset(Sprite::Create(TimeTexture_[i], {0, 0}));
	}
}

void TimeLimit::Update() 
{ timer_ -= 1; }

void TimeLimit::Draw() 
{
	if (timer_ > 60*50 && timer_ <= 60*60) {
		TimeSprite_[0]->Draw();
	}
	if (timer_ > 60 * 40 && timer_ <= 60 * 50) {
		TimeSprite_[1]->Draw();
	}
	if (timer_ > 60 * 30 && timer_ <= 60 * 40) {
		TimeSprite_[2]->Draw();
	}
	if (timer_ > 60 * 20 && timer_ <= 60 * 30) {
		TimeSprite_[3]->Draw();
	}
	if (timer_ > 60 * 10 && timer_ <= 60 * 20) {
		TimeSprite_[4]->Draw();
	}
	if (timer_ > 60 * 9 && timer_ <= 60 * 10) {
		TimeSprite_[5]->Draw();
	}
	if (timer_ > 60 * 8 && timer_ <= 60 * 9) {
		TimeSprite_[6]->Draw();
	}
	if (timer_ > 60 * 7 && timer_ <= 60 * 8) {
		TimeSprite_[7]->Draw();
	}
	if (timer_ > 60 * 6 && timer_ <= 60 * 7) {
		TimeSprite_[8]->Draw();
	}
	if (timer_ > 60 * 5 && timer_ <= 60 * 6) {
		TimeSprite_[9]->Draw();
	}
	if (timer_ > 60 * 4 && timer_ <= 60 * 5) {
		TimeSprite_[10]->Draw();
	}
	if (timer_ > 60 * 3 && timer_ <= 60 * 4) {
		TimeSprite_[11]->Draw();
	}
	if (timer_ > 60 * 2 && timer_ <= 60 * 3) {
		TimeSprite_[12]->Draw();
	}
	if (timer_ > 60 * 1 && timer_ <= 60 * 2) {
		TimeSprite_[13]->Draw();
	}
	if (timer_ > 0 && timer_ <= 60 * 1) {
		TimeSprite_[14]->Draw();
	}
}

void TimeLimit::Reset() 
{ timer_ = 60 * 60; }