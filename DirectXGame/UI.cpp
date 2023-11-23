#include "UI.h"

void UI::Initialize() {
	textureUI[0] = TextureManager::Load("Sample.png");
	textureUI[1] = TextureManager::Load("uvChecker.png");
	textureUI[2] = TextureManager::Load("uvChecker.png");

	uisprites_[0] =
	    Sprite::Create(textureUI[0], {1000.0f, 700.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	uisprites_[1] =
	    Sprite::Create(textureUI[1], {500.0f, 700.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	uisprites_[2] =
	    Sprite::Create(textureUI[2], {1200.0f, 700.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

}

void UI::Update() {}

void UI::Draw() { 
	uisprites_[0]->Draw(); 
	uisprites_[1]->Draw();
	uisprites_[2]->Draw();

}
