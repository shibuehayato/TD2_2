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

Vector3 PlayerBullet::GetWorldPosition() 
{
   // ワールド座標を入れる変数
   Vector3 worldPos;
   // ワールド行列の平行移動成分を取得 (ワールド座標)
   worldPos.x = worldTransform_.matWorld_.m[3][0];
   worldPos.y = worldTransform_.matWorld_.m[3][1];
   worldPos.z = worldTransform_.matWorld_.m[3][2];
   
   return worldPos;
}

void PlayerBullet::OnCollision() 
{ isDead_ = true; }
