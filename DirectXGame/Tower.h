#pragma once
#include "Model.h"
#include "WorldTransform.h"
class Tower {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
};
