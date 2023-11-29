#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "BaseCharacter.h"
#include"PlayerBullet.h"
#include"Beam.h"
#include"Wall.h"
#include<list>
#include"Speed.h"

class Player : public BaseCharacter {
public:
	~Player();

	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(const ViewProjection& viewProjection) override;

	void Attack();

	const WorldTransform& GetWorldTransform() { return worldTransformBody_; }

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	bool const IsSpeed() { return isspeed_; }

	Vector3 GetWorldPosition();

	// 浮遊ギミック初期化
	void InitializeFloatingGimmick();
	// 浮遊ギミック更新
	void UpdateFloatingGimmick();

	

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return playerbullets_; }

	// ビームを取得
	const std::unique_ptr<Beam>& GetBeam() const { return beam_; }

	bool const IsdurationAlive() { return durationAlive_; }

	// 壁を取得
	const std::unique_ptr<Wall>& GetWall() const { return wall_; }

private:
	// ワールド変換データ
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	WorldTransform worldTransform_;

	// キーボード入力
	Input* input_ = nullptr;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

	// 浮遊の振幅<m>
	float range_ = 0.4f;

	float head_[3] = {0, 1.8f, 0};
	float body_[3] = {0, 0.2f, 0};
	float l_arm[3] = {-0.6f, 1.5f, 0};
	float r_arm[3] = {0.6f, 1.5f, 0};

	Model* modelBullet_ = nullptr;

	// std::unique_ptr<PlayerBullet> playerbullet_;
	PlayerBullet* playerbullet_ = nullptr;
	std::list<PlayerBullet*> playerbullets_;

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	// 弾のクールタイム
	int32_t cooltimer_;

	// デスフラグ
	bool isDead_ = false;

	std::unique_ptr<Beam> beam_;
	Model* modelbeam_ = nullptr;
	int32_t duration = 0;

	bool durationAlive_ = false;

	std::unique_ptr<Wall> wall_;

	int32_t wallcolltimer_;
	bool wallAlive_ = false;

	std::unique_ptr<Speed> speed_;
	bool isspeed_ = false;
	
	
	Model* modelwall_ = nullptr;

};
