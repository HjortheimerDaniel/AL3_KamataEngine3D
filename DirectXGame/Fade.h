#pragma once
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DirectXCommon.h"

class Fade
{

public:

	void Initialize();

	void Update();

	void Draw(ID3D12GraphicsCommandList* commandList);

private:

	DirectXCommon* dxCommon_ = nullptr;
	Sprite* sprite_ = nullptr;
	uint32_t textureHandle_ = 0;
};

