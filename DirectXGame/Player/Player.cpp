﻿#include "Player.h"
#include <cassert>
#include <ImGuiManager.h>

Player::~Player()
{
	for (PlayerBullet* playerbullet : playerbullets_)
	{
		delete playerbullet;
	}



}


void Player::Initialize(const std::vector<Model*>& models) {
	
	// 基底クラスの初期化
	BaseCharacter::Initialize(models);

	worldTransformHead_.translation_ = {0, 1, 0};
	worldTransformBody_.translation_ = {0, 0, 0};
	worldTransformL_arm_.translation_ = {-0.5f, 1.5, 0};
	worldTransformR_arm_.translation_ = {0.5, 1.5, 0};
	
	worldTransformHead_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	
	// シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	
	InitializeFloatingGimmick();

	modelbeam_ = Model::Create();

	beam_ = std::make_unique<Beam>();
	beam_->Initialize(modelbeam_,worldTransformBody_.translation_);

	//wall_ = std::make_unique<Wall>();
	//
	//modelwall_ = Model::Create();

	//wall_->Initialize(modelwall_);
	beam_->Initialize(modelbeam_,worldTransformBody_.translation_);
	
	
	modelBullet_ = Model::CreateFromOBJ("bullet",true);
}

void Player::Update() { 
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_Y&&durationAlive_==false) {
		
		durationAlive_ = true;
	}
	if (durationAlive_||duration>=1) {
		duration++;
	}
	if (duration >=100)
	{
		durationAlive_ = false;
	}
	if (duration >= 200) {
		
		duration = 0;
		
	} 

	/*if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X &&wallAlive_ == false)
	{
		wallAlive_ = true;
	}
	
	if (wallAlive_)
	{
		wallcolltimer_++;
	}
	if (wallcolltimer_ >= 300)
	{
		wallAlive_ = false;
		wallcolltimer_ = 0;
	}*/
	
	// ゲームパッドが有効の場合if文が通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	
		// 速さ
		const float speed = 0.3f;

	// 移動量
		Vector3 move = {0, 0, 0};

		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed;
		move.z += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed;

		// カメラの角度から回転行列を計算する
		Matrix4x4 RotationMatrix = MakeRotateMatrix(viewProjection_->rotation_);

		// オフセットをカメラの回転に合わせて回転させる
		move = TransformNormal(move, RotationMatrix);
		

			worldTransformHead_.rotation_.y = std::atan2(move.x, move.z);
			worldTransformBody_.rotation_.y = std::atan2(move.x, move.z);
			worldTransformL_arm_.rotation_.y = std::atan2(move.x, move.z);
			worldTransformR_arm_.rotation_.y = std::atan2(move.x, move.z);
		
			beam_->Update(move);
		    //wall_->Update(move,worldTransformBody_.translation_);

		// 座標移動
		worldTransformHead_.translation_ = Add(worldTransformHead_.translation_, move);
		worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, move);
		worldTransformL_arm_.translation_ = Add(worldTransformL_arm_.translation_, move);
		worldTransformR_arm_.translation_ = Add(worldTransformR_arm_.translation_, move);

	
	} 

	   

	UpdateFloatingGimmick();

	worldTransformHead_.UpdateMatrix(); 
    worldTransformBody_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();

	Attack();

	for (PlayerBullet* playerbullet : playerbullets_)
	{
		playerbullet->Update();
	}

	playerbullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	
	


}

void Player::Draw(const ViewProjection& viewProjection) {
	// 3Dモデル描画
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);

	for (PlayerBullet* playerbullet : playerbullets_)
	{
		playerbullet->Draw(viewProjection);
	}

	if (duration>=1&&duration<=100) {
		beam_->Draw(viewProjection);
	}

	/*if (wallcolltimer_>=1&&wallcolltimer_<=280)
	{
		wall_->Draw(viewProjection);
	}*/

}




Vector3 Player::GetWorldPosition() { 
	Vector3 worldPos;
	worldPos.x = worldTransformHead_.matWorld_.m[3][0];
	worldPos.y = worldTransformHead_.matWorld_.m[3][1];
	worldPos.z = worldTransformHead_.matWorld_.m[3][2];
	return worldPos; 
}

void Player::InitializeFloatingGimmick() { 
	floatingParameter_ = 0.0f;
}

void Player::UpdateFloatingGimmick() {
	// 浮遊移動のサイクル<frame>
	const uint16_t cycle = 60;
	// 1フレームでのパラメータ加算値
	const float step = 2.0f * 3.14f / cycle;

	// パラメータを1ステップ分加算
	floatingParameter_ += step;
	// 2πを超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * 3.14f);

	// 浮遊を座標に反映
	worldTransformHead_.translation_.y = std::sin(floatingParameter_) * range_ + head_[1];
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * range_ + body_[1];
	worldTransformL_arm_.translation_.y = std::sin(floatingParameter_) * range_ + l_arm[1];
	worldTransformR_arm_.translation_.y = std::sin(floatingParameter_) * range_ + r_arm[1];

	// 両腕をぶらぶらさせる
	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * range_;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * range_;

	

}

void Player::Attack() {
	if (cooltimer_ <= 10) {
        cooltimer_++;
	}

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B&&cooltimer_>=10) {
		PlayerBullet* newplayerbullet_ = new PlayerBullet();
		const float playerbulletspeed = 1.0f;
		Vector3 velocity = {0.0f, 0.0f, playerbulletspeed};

		velocity = TransformNormal(velocity, worldTransformHead_.matWorld_);

		newplayerbullet_->Initialize(modelBullet_,worldTransformHead_.translation_,velocity);

		playerbullets_.push_back(newplayerbullet_);
		cooltimer_ = 0;
	}

}



void Player::OnCollision()
{ isDead_ = true; }