#include "StageClearText.h"

StageClearText::StageClearText()
{
}

StageClearText::~StageClearText()
{
}

void StageClearText::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = { titleSize, titleSize, titleSize };
	//theta = 0.0f;
	//amplitude = 2.0f;
}

void StageClearText::Update()
{
	worldTransform_.UpdateMatrix();
}

void StageClearText::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}


