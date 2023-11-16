#include "PlayerBullet.h"
#include<cassert>

void PlayerBullet::Initialize(Model* model,Vector3 position,Vector3 velocity) { 
	assert(model);
	model_ = model;

	worldTransform_.translation_ = position;
	worldTransform_.Initialize();
	velocity_ = velocity;
}

void PlayerBullet::Update() { 
	
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	
	worldTransform_.UpdateMatrix();

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
model_->Draw(worldTransform_, viewProjection);

}
