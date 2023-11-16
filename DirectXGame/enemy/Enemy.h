﻿#pragma once
#include "BaseCharacter.h"

// タワークラスの前方宣言
class Tower;

class GameScene;

class Enemy : public BaseCharacter
{
public:
	void Initialize(const std::vector<Model*>& models, const Vector3& position);
	void Update() override;
	void Draw(const ViewProjection& viewProjection) override;
	const WorldTransform& GetWorldTransform() { return worldTransformBody_; }

	void SetTower(Tower* tower) { tower_ = tower; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

private:
	// ワールド変換データ
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	// タワー
	Tower* tower_ = nullptr;

	// デスフラグ
	bool isDead_ = false;

	// ゲームシーン
	GameScene* gameScene_ = nullptr;
};