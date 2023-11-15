#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"MyMath.h"
#include"input.h"


class OverheadCamera {
public:
	void Initialize();

	void Update();

	void Timer();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	bool IsCameraActive() { return isCameraActive; }

	

	private:
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	Input* input_ = nullptr;

	bool isCameraActive = false;

	int32_t cooltimer_;

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	
};
