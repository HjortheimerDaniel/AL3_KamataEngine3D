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
	//worldTransform_.rotation_.y = 3.14159265359f;

}

void TitleText::Update()
{
	worldTransform_.translation_.x = -50.0f;

	worldTransform_.UpdateMatrix();

}

void TitleText::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
