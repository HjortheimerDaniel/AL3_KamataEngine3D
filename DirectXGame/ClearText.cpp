#include "ClearText.h"

ClearText::ClearText()
{
}

ClearText::~ClearText()
{
}

void ClearText::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = { titleSize, titleSize, titleSize };
}

void ClearText::Update()
{
	timer++;

	if(timer <= 60)
	{
		worldTransform_.translation_.z -= 0.05f;

	}
	else 
	{
		worldTransform_.translation_.z += 0.05f;
	}

	if (timer >= 120) 
	{
		timer = 0;
	}
	
	worldTransform_.UpdateMatrix();
}

void ClearText::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
