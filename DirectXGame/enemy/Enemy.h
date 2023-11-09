#pragma once
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:
	void Initialize(const std::vector<Model*>& models) override;
	void Update() override;
	void Draw(const ViewProjection& viewProjection) override;
	const WorldTransform& GetWorldTransform() { return worldTransformBody_; }

private:
	// ワールド変換データ
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
};