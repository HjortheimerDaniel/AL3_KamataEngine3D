#include "TitlePlayer.h"
#include "imgui.h"

TitlePlayer::TitlePlayer()
{
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = 3.14159265359f / 2;
	worldTransform_.scale_ = { titlePlayerSize, titlePlayerSize, titlePlayerSize };
}

void TitlePlayer::Update()
{
	worldTransform_.translation_.x += 1;
	
	if (worldTransform_.translation_.x >= 100.0f) 
	{
		worldTransform_.translation_.x = -100.0f;
	}

	ImGui::Begin("Window");
	ImGui::DragFloat("X pos %f", &worldTransform_.translation_.x,1);
	ImGui::End();

	worldTransform_.UpdateMatrix();
}

void TitlePlayer::Draw()
{

	model_->Draw(worldTransform_, *viewProjection_);
}
