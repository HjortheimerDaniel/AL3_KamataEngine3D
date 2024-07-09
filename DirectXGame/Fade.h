#pragma once
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DirectXCommon.h"

enum class Status 
{
	None,
	FadeIn,
	FadeOut,
};


class Fade
{

public:

	void Initialize();

	void Update();

	void Start(Status status, float duration);

	void Stop();

	bool IsFinished();

	void ResetCounter();

	void SetCounter_(float counter) {counter_ = counter; };
	
	void Draw();

private:

	DirectXCommon* dxCommon_ = nullptr;
	Sprite* sprite_ = nullptr;
	uint32_t textureHandle_ = 0;
	Status status_ = Status::None;
	float duration_ = 0.0f;
	float counter_ = 0.0f;
};

