#include "Enemy.h"

void Enemy::Initialize(const std::vector<Model*>& models) 
{
	// 基底クラスの初期化
	BaseCharacter::Initialize(models);

	worldTransformBody_.translation_ = {3.0f, -0.5f, 0};
	worldTransformL_arm_.translation_ = {2.1f,0.6f,0};
	worldTransformR_arm_.translation_ = {3.9f, 0.6f, 0};

	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
}

void Enemy::Update() 
{ 
	worldTransformBody_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	// 3Dモデル描画
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformL_arm_, viewProjection);
	models_[2]->Draw(worldTransformR_arm_, viewProjection);
}