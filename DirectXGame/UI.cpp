#include "UI.h"

void UI::Initialize() {
	texturesUI[0] = TextureManager::Load("UI.png");



	uisprites_[0] =
	    Sprite::Create(texturesUI[0], {600.0f,350.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	

}

void UI::Update() {}

void UI::Draw() { 
	uisprites_[0]->Draw(); 
	

}
