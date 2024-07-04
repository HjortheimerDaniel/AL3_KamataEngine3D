#include "TitleText.h"

TitleText::TitleText()
{

}

TitleText::~TitleText()
{
}

void TitleText::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = { titleSize, titleSize, titleSize };

}

void TitleText::Update()
{
	if (worldTransform_.translation_.y >= 1.0f) 
	{
		worldTransform_.translation_.y--;
	}
	worldTransform_.UpdateMatrix();
}

void TitleText::Draw()
{

	model_->Draw(worldTransform_, *viewProjection_);
}

float TitleText::EaseIn(float x)
{
	float pi = 3.1419f;
	return 1.0f - cosf((x * pi / 2.0f));

}



