#include "Enemy.h"
#include "MyMath.h"
#include "Tower.h"
#include <cmath>

void Enemy::Initialize(const std::vector<Model*>& models, const Vector3& position) {
	// 基底クラスの初期化
	BaseCharacter::Initialize(models);

	/*worldTransformBody_.translation_ = {37.0f, -0.5f, 35};
	worldTransformL_arm_.translation_ = {36.1f,0.6f,35};
	worldTransformR_arm_.translation_ = {37.9f, 0.6f, 35};*/

	worldTransformBody_.translation_ = position;
	worldTransformL_arm_.translation_ = position;
	worldTransformR_arm_.translation_ = position;

	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
}

void Enemy::Update() 
{ 
	// 敵の速度
	float enemySpeed = 0.1f;
	Vector3 velocity(0, 0, enemySpeed);

	Vector3 towerPosition = tower_->GetWorldPosition();
	Vector3 enemyPosition = this->GetWorldPosition();
	velocity = Subtract(towerPosition, enemyPosition);
	velocity = Normalize(velocity);
	velocity.x *= enemySpeed;
	velocity.y *= enemySpeed;
	velocity.z *= enemySpeed;

	worldTransformBody_.rotation_.y = std::atan2(velocity.x, velocity.z);
	worldTransformL_arm_.rotation_.y = std::atan2(velocity.x, velocity.z);
	worldTransformR_arm_.rotation_.y = std::atan2(velocity.x, velocity.z);

	worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, velocity);
	worldTransformL_arm_.translation_ = Add(worldTransformL_arm_.translation_, velocity);
	worldTransformR_arm_.translation_ = Add(worldTransformR_arm_.translation_, velocity);

	worldTransformBody_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	if (isDead_ == false) {
		// 3Dモデル描画
		models_[0]->Draw(worldTransformBody_, viewProjection);
		models_[1]->Draw(worldTransformL_arm_, viewProjection);
		models_[2]->Draw(worldTransformR_arm_, viewProjection);
	}
}

Vector3 Enemy::GetWorldPosition() 
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得 (ワールド座標)
	worldPos.x = worldTransformBody_.matWorld_.m[3][0];
	worldPos.y = worldTransformBody_.matWorld_.m[3][1];
	worldPos.z = worldTransformBody_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::OnCollision()
{ isDead_ = true; }