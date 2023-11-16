#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"MyMath.h"

class PlayerBullet {
public:
	void Initialize(Model* model, Vector3 position, Vector3 velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }

	static const int32_t kLifeTime = 60 * 5;

	private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Vector3 velocity_;

	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;

};
