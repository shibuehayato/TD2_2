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

void Tower::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Tower::GetWorldPosition() 
{ 
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得 (ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}