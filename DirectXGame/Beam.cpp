#include "Beam.h"
#include<cassert>
#include "MyMath.h"
void Beam::Initialize(Model* model, Vector3 position ) { 
	assert(model);
	model_ = model;
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.3f};
	
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

Vector3 Beam::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Beam::GetWorldRadius() { 
Vector3 worldRadius;

	worldRadius.x = worldTransform_.scale_.x;
	worldRadius.y = worldTransform_.scale_.y;
	worldRadius.z = worldTransform_.scale_.z;
	return worldRadius;

}

void Beam::OnCollision() {}
