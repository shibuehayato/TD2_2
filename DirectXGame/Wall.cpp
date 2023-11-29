#include "Wall.h"

#include<cassert>
void Wall::Initialize(Model* model) 
{ 
	assert(model);
	model_ = model;
	
	worldTransform_.scale_ = {1.0f, 20.0f, 20.0f};
	worldTransform_.Initialize();

	
	
}



void Wall::Update(Vector3 move,Vector3 position) { 


	// ゲームパッドが有効の場合if文が通る
if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		
			 istimer_ = true;
		} else if (istimer_==false)
	{
			 worldTransform_.rotation_.y = std::atan2(move.x, move.z);
			worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	
	}
		if (istimer_||timer_>=1) {
			timer_++;
		}
		if (timer_ >= 280)
		{
			istimer_ = false;
		}
		if (timer_ >= 300)
		{
			
			worldTransform_.translation_ = position;
			timer_ = 0;
		}
}
	    worldTransform_.UpdateMatrix();
	
		ImGui::Begin("Windows");
	    ImGui::DragInt("Timer", &timer_, 0.01f);
	    ImGui::End();

}

void Wall::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Wall::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Wall::GetWorldRadius() {
	Vector3 worldRadius;

	worldRadius.x = worldTransform_.scale_.x;
	worldRadius.y = worldTransform_.scale_.y;
	worldRadius.z = worldTransform_.scale_.z;
	return worldRadius;
}

void Wall::OnCollision() {}
