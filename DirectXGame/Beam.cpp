#include "Beam.h"
#include<cassert>
#include "MyMath.h"
void Beam::Initialize(Model* model, Vector3 position ) { 
	assert(model);
	model_ = model;
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.Initialize();

	

	// シングルトンインスタンスを取得
	input_ = Input::GetInstance();



}

void Beam::Update(Vector3 move) { 
	// ゲームパッドが有効の場合if文が通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		

		worldTransform_.rotation_.y = std::atan2(move.x, move.z);
		

		// 座標移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	
	} 
	
	
	worldTransform_.UpdateMatrix();



}

void Beam::Draw(const ViewProjection& viewProjection) 
{ 
	model_->Draw(worldTransform_, viewProjection);


}
