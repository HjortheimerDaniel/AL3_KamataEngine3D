#include "Wind.h"

Wind::Wind()
{
}

Wind::~Wind()
{
}

void Wind::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	startPos = worldTransform_.translation_;
	worldTransform_.scale_.y = 3.0f;

}

void Wind::Update()
{
	worldTransform_.UpdateMatrix();
}

void Wind::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);

}
