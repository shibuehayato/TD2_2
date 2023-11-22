#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"Input.h"
#include"MyMath.h"

class Wall {
public:
	void Initialize(Model* model,const Vector3& position,Vector3 velocity);
	
	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

		// キーボード入力
	Input* input_ = nullptr;

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	Vector3 velocity_;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

};
