#include "Fade.h"
#include "TextureManager.h"

void Fade::Initialize()
{
	textureHandle_ = TextureManager::Load("fader.png");
	sprite_ = Sprite::Create(textureHandle_, { 500, 50 });
	sprite_->SetSize({ 1280.0f, 720.0f });
	sprite_->SetColor({ 0,0,0,1 });
}

void Fade::Update()
{
}

void Fade::Draw(ID3D12GraphicsCommandList* commandList)
{
	//ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	Sprite::PreDraw(commandList);
	sprite_->Draw();
	Sprite::PostDraw();

}
