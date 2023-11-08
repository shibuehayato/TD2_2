#include "Tower.h"
#include <cassert>

void Tower::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {3.0f, 1.9f, 0.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};


}

void Tower::Update() { 
	
	
	worldTransform_.UpdateMatrix(); }

void Tower::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }