#pragma once
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DirectXCommon.h"

class GreyPauseVeil
{
public:

	void Initialize();

	void Update();

	void Draw();

private:

	DirectXCommon* dxCommon_ = nullptr;
	Sprite* sprite_ = nullptr;
	uint32_t textureHandle_ = 0;

};

