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
#include "Fade.h"
#include "Skydome.h"


class TitleScene
{
public:

	TitleScene();

	~TitleScene();

	void Initialize();
	
	void Update();

	void Draw();

	bool GetIsFinished() const { return finished_; };

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	WorldTransform worldTransform_;
	Model* playerModel_ = nullptr;
	Model* textModel_ = nullptr;
	Model* textModel2_ = nullptr;
	Model* textModel3_ = nullptr;
	Model* textModel4_ = nullptr;
	Model* textModel5_ = nullptr;
	Model* textModel6_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	TitlePlayer* titlePlayer_ = nullptr;
	TitlePlayer* titlePlayer2_ = nullptr;
	TitlePlayer* titlePlayer3_ = nullptr;
	TitleText* titleText_ = nullptr;
	TitleText* titleText2_ = nullptr;
	TitleText* titleText3_ = nullptr;
	TitleText* titleText4_ = nullptr;
	TitleText* titleText5_ = nullptr;
	TitleText* titleText6_ = nullptr;
	TitleText* titleText7_ = nullptr;
	bool finished_ = false;
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;
	int clicks_ = 0;
	enum class Phase
	{
		kFadeIn,
		kMain,
		kFadeOut,
	};

	Phase phase_ = Phase::kFadeIn;
	Model* modelSkydome_ = nullptr;
	Skydome* skydome_ = nullptr;
	int enterTimer_ = 0;
};

