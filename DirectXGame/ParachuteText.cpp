#include "ParachuteText.h"

ParachuteText::ParachuteText()
{
}

ParachuteText::~ParachuteText()
{
}

void ParachuteText::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = { textSize, textSize, textSize };
	worldTransform_.translation_.z = -10.0f;
}

void ParachuteText::Update()
{
	worldTransform_.UpdateMatrix();
}

void ParachuteText::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
