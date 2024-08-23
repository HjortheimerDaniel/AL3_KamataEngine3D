#include "Fade.h"
#include "TextureManager.h"
#include "Input.h"
#include "algorithm"
#include <iostream>
#include "Windows.h"

void Fade::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	textureHandle_ = (TextureManager::Load("blackfade.png"));
	sprite_ = Sprite::Create(textureHandle_, { 0, 0 });
	sprite_->SetSize({ 1920.0f, 1080.0f });
	sprite_->SetColor({ 0,0,0,1 });
}

void Fade::Update()
{
	switch (status_)
	{
	case Status::None:
		break;
	case Status::FadeIn:
		
		counter_ += 1.0f / 60.0f;
		if (counter_ >= duration_)
		{
			counter_ = duration_;

		}
		sprite_->SetColor({ 0,0,0, std::clamp(1-counter_ / duration_, 0.0f, 1.0f) });
		
		break;
	case Status::FadeOut:
		counter_ += 1.0f / 60.0f;
		if (counter_ >= duration_) 
		{
			counter_ = duration_;
		}
		sprite_->SetColor({ 0,0,0, std::clamp(counter_ / duration_, 0.0f, 1.0f) });
		break;
	default:
		break;
	}
}

void Fade::Start(Status status, float duration)
{
	status_ = status;
	duration_ = duration;
	counter_ = 0.0f;
}

void Fade::Stop()
{
	status_ = Status::None;
	counter_ = 0.0f;
}

bool Fade::IsFinished()
{
	switch (status_)
	{
	case Status::None:
		break;
	case Status::FadeIn:

	case Status::FadeOut:
		if(counter_ >= duration_)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	return false;
}

void Fade::ResetCounter()
{
	if (counter_ >= 0.0f) 
	{
		counter_ = 0.0f;
	}
}

void Fade::Draw()
{
	if (status_ == Status::None)
	{
		return;
	}

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	Sprite::PreDraw(commandList);
	sprite_->Draw();
	Sprite::PostDraw();
	dxCommon_->ClearDepthBuffer();
	
}
