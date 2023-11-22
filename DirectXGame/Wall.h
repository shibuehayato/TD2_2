#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"Input.h"
#include"MyMath.h"
#include"ImGuiManager.h"

class Wall {
public:
	void Initialize(Model* model);
	
	void Update(Vector3 move,Vector3 position);

	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

		// キーボード入力
	Input* input_ = nullptr;

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;



int32_t timer_;
	bool istimer_;
	

};
