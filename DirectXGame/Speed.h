#pragma once
#include <cstdint>
#include"Input.h"
#include"ImGuiManager.h"
class Speed {
public:
	void Initialize();

	void Update();

	bool const IsTime() { return istime_; }

	static const int Time = 780;

	private:
	int32_t cooltime_;

	bool istime_ = false;

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

};
