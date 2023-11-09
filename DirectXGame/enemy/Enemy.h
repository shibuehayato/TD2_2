#pragma once
#include "BaseCharacter.h"

// タワークラスの前方宣言
class Tower;

class Enemy : public BaseCharacter
{
public:
	void Initialize(const std::vector<Model*>& models) override;
	void Update() override;
	void Draw(const ViewProjection& viewProjection) override;
	const WorldTransform& GetWorldTransform() { return worldTransformBody_; }

	void SetTower(Tower* tower) { tower_ = tower; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

private:
	// ワールド変換データ
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	// タワー
	Tower* tower_ = nullptr;
};