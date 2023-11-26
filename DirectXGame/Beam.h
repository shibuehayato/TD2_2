#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include "Input.h"
class Beam {
public:
	void Initialize(Model* model,Vector3 position);

	void Update(Vector3 move);

	void Draw(const ViewProjection& viewProjection);

	

	

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	// キーボード入力
	Input* input_ = nullptr;

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	

	

};
