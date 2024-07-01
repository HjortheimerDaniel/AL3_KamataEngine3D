#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "TitlePlayer.h"
#include "TitleText.h"


class TitleScene
{
public:

	TitleScene();

	~TitleScene();

	void Initialize();
	
	void Update();

	void Draw();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	WorldTransform worldTransform_;
	Model* playerModel_ = nullptr;
	Model* textModel_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	TitlePlayer* titlePlayer_ = nullptr;
	TitleText* titleText_ = nullptr;

};

