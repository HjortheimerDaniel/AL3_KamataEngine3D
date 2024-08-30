#pragma once
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DirectXCommon.h"

class GreyPauseVeil
{
public:

	void Initialize(bool isPaused);

	void Update();


	void Draw();

private:

	DirectXCommon* dxCommon_ = nullptr;
	Sprite* sprite_ = nullptr;
	Sprite* sprite2_ = nullptr;
	uint32_t textureHandle_ = 0;
	uint32_t textureHandle2_ = 0;
	bool isPaused_ = false;

};

