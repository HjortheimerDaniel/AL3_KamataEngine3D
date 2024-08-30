#include "GreyPauseVeil.h"
#include "TextureManager.h"
#include "Input.h"
#include "algorithm"
#include <iostream>
#include "Windows.h"


void GreyPauseVeil::Initialize(bool isPaused)
{
	isPaused_ = isPaused;
	dxCommon_ = DirectXCommon::GetInstance();
	textureHandle_ = (TextureManager::Load("greypause.png"));
	textureHandle2_ = (TextureManager::Load("pauseText.png"));
	sprite_ = Sprite::Create(textureHandle_, { 0, 0 });
	sprite2_ = Sprite::Create(textureHandle2_, { 0, 0 });
	sprite_->SetSize({ 1920.0f, 1080.0f });
	sprite2_->SetSize({ 1280.0f, 720.0f });
	sprite_->SetColor({ 0,0,0,1 });
}

void GreyPauseVeil::Update()
{
}

void GreyPauseVeil::Draw()
{
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	Sprite::PreDraw(commandList);
	sprite_->Draw();
	if (isPaused_) 
	{
		sprite2_->Draw();
	}
	Sprite::PostDraw();
	dxCommon_->ClearDepthBuffer();
}
