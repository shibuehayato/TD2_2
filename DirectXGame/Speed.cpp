#include "Speed.h"

void Speed::Initialize() {

	cooltime_ = 0; 
}

void Speed::Update() { 
	
	if (cooltime_ >= 1) {
		cooltime_--;
	}
	
	// ゲームパッドが有効の場合if文が通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (cooltime_ <= 0 && joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
			istime_ = true;
			cooltime_ = Time;
		}
		
		if (cooltime_ <=600)
		{
			istime_ = false;
		}
	}



}
