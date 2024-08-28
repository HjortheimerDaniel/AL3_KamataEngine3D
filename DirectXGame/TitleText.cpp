#include "TitleText.h"
#define _USE_MATH_DEFINES
#include <math.h>

TitleText::TitleText()
{

}

TitleText::~TitleText()
{
}

void TitleText::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, bool isFloating)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	isFloating_ = isFloating;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = { titleSize, titleSize, titleSize };
	theta = 0.0f;
	amplitude = 2.0f;
}

void TitleText::Update()
{
	if (isFloating_)
	{
		theta += float(M_PI) / 150.0f;
		worldTransform_.translation_.y = sinf(theta) * amplitude + 3.0f;
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



