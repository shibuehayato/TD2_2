#include "Wall.h"
#include<cassert>
void Wall::Initialize(Model* model) 
{ assert(model);
	model_ = model;
	worldTransform_.Initialize();

}
