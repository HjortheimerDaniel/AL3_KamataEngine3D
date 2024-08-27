#include "GameClearText.h"
#define _USE_MATH_DEFINES
#include <math.h>

GameClearText::GameClearText()
{
}

GameClearText::~GameClearText()
{
}

void GameClearText::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, float startpos, float startUpdate, float amplitude)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	startpos_ = startpos;
	startUpdate_ = startUpdate;
	amplitude_ = amplitude;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = { titleSize, titleSize, titleSize };
	theta = 0.0f;
}

void GameClearText::Update()
{
	if (updateTimer_ < startUpdate_)
	{
		updateTimer_++;
	}
	if (updateTimer_ >= startUpdate_) 
	{
		theta += float(M_PI) / 150.0f;
		worldTransform_.translation_.y = sinf(theta) * amplitude_ + startpos_;
		
	}
	worldTransform_.UpdateMatrix();

}

void GameClearText::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}


