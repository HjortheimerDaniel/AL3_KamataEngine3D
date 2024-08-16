#include "Parachute.h"

Parachute::Parachute()
{
}

Parachute::~Parachute()
{
}

void Parachute::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Parachute::Update()
{
	worldTransform_.UpdateMatrix();
}

void Parachute::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
