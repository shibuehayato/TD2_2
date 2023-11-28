#include "UI.h"

void UI::Initialize() {
	texturesUI[0] = TextureManager::Load("Sample.png");
	texturesUI[1] = TextureManager::Load("uvChecker.png");
	
	texturesUI[3] = TextureManager::Load("debugfont.png");
	texturesUI[4] = TextureManager::Load("debugfont.png");
	


	uisprites_[0] =
	    Sprite::Create(texturesUI[0], {1000.0f, 700.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	uisprites_[1] =
	    Sprite::Create(texturesUI[1], {500.0f, 700.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	
	uisprites_[3] =
	    Sprite::Create(texturesUI[3], {950.0f, 700.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	uisprites_[4] =
	    Sprite::Create(texturesUI[4], {450.0f, 700.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	

}

void UI::Update() {}

void UI::Draw() { 
	uisprites_[0]->Draw(); 
	uisprites_[1]->Draw();
	
	uisprites_[3]->Draw();
	uisprites_[4]->Draw();


}
