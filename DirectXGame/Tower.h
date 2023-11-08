#pragma once
#include "Model.h"
#include "WorldTransform.h"
class Tower {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

	

private:
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;

	

};
