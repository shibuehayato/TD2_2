#include "OverheadCamera.h"

void OverheadCamera::Initialize() { viewProjection_.Initialize();
	worldTransform_.Initialize();
	viewProjection_.translation_ = {0.0f, 50.0f, -20.0f};
	viewProjection_.rotation_ = {-29.0f, 0.0f, 0.0f};
	input_ = Input::GetInstance();
}



void OverheadCamera::Update() { viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	const float Cameraspeed = 0.01f;

	
	if (input_->PushKey(DIK_RIGHT)) {
		viewProjection_.rotation_.y += Cameraspeed;
	}else if (input_->PushKey(DIK_LEFT)) {
		viewProjection_.rotation_.y -= Cameraspeed;
	} else if (input_->PushKey(DIK_UP)) {
		viewProjection_.rotation_.x -= Cameraspeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.rotation_.x += Cameraspeed;
	}
	
	// ゲームパッドが有効の場合if文が通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 回転する速さ
		const float speed = 0.05f;
	

			viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * speed;
			viewProjection_.rotation_.x += (float)joyState.Gamepad.sThumbRY / SHRT_MAX * speed;
		    if (viewProjection_.rotation_.x <= -29.8f) {
			    viewProjection_.rotation_.x = -29.8f;
		    }
		    if (viewProjection_.rotation_.x >= -27.3f) {
			    viewProjection_.rotation_.x = -27.3f;
		    }

			if (joyState.Gamepad.wButtons&XINPUT_GAMEPAD_LEFT_THUMB && cooltimer_ >= 10) {

			isCameraActive = true;
			cooltimer_ = 0;

		} else {
			isCameraActive = false;
		}
	}

	
	
	



	viewProjection_.UpdateMatrix();
}

void OverheadCamera::Timer()
{ 
	cooltimer_++;



}