#include "Wall.h"

#include<cassert>
void Wall::Initialize(Model* model,const Vector3& position,Vector3 velocity) 
{ 
	assert(model);
	model_ = model;
	worldTransform_.translation_.x = position.x;
	worldTransform_.translation_.y = position.y;
	worldTransform_.translation_.z = position.z;
	worldTransform_.scale_ = {1.0f, 1.0f, 20.0f};
	worldTransform_.Initialize();

	velocity_ = velocity;

}

void Wall::Update() { 
	
	// 移動量
	Vector3 move = {0, 0, 0};

	

	worldTransform_.translation_ = Add(worldTransform_.translation_,move);

	worldTransform_.UpdateMatrix();


}

void Wall::Draw(const ViewProjection& viewProjection) 
{ 
	model_->Draw(worldTransform_, viewProjection);


}
