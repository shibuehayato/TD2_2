#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"

class OverheadCamera {
public:
	void Initialize();

	void Update();

	private:
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;
};
