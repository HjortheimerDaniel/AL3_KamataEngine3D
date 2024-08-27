#pragma once
#include "DirectXCommon.h"
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "TitlePlayer.h"
#include "GameClearText.h"
#include "Fade.h"
#include <vector>
#include "struct.h"

class GameClearScreen
{
public:

	GameClearScreen();

	~GameClearScreen();

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
	Model* textModel[MAXTHANKYOU] =
	{
		{Model::CreateFromOBJ("gamecleartext1", true)},  {Model::CreateFromOBJ("a", true)}, {Model::CreateFromOBJ("r", true)},
		{Model::CreateFromOBJ("ga", true)}, {Model::CreateFromOBJ("to", true)}, {Model::CreateFromOBJ("u", true)},
		{Model::CreateFromOBJ("go", true)}, {Model::CreateFromOBJ("za", true)}, {Model::CreateFromOBJ("i", true)},
		{Model::CreateFromOBJ("ma", true)}, {Model::CreateFromOBJ("shi", true)}, {Model::CreateFromOBJ("ta", true)},

	};
	float startY = -10.0f;
	Vector3 textPos_[MAXTHANKYOU] =
	{
		{ -40.0f, 3.0f, 1.0f }, { -40.0f, startY, 1.0f }, { -32.0f, startY, 1.0f },
		{ -24.0f, startY, 1.0f },{ -16.0f, startY, 1.0f }, { -8.0f, startY, 1.0f },
		{ -0.0f, startY, 1.0f }, { 8.0f, startY, 1.0f }, { 16.0f, startY, 1.0f },
		{ 24.0f, startY, 1.0f }, { 32.0f, startY, 1.0f }, { 40.0f, startY, 1.0f },

	};
	float startPos[MAXTHANKYOU] =
	{
		7.0f, -10.0f, -10.0f,
		-10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f, -10.0f,
	};
	float addTime = 1.5f;
	float startUpdate[MAXTHANKYOU] =
	{
		5.0f, 10.0f * addTime, 15.0f * addTime,
		20.0f * addTime, 25.0f * addTime, 30.0f * addTime,
		35.0f * addTime, 40.0f * addTime, 45.0f * addTime,
		50.0f * addTime, 55.0f * addTime, 60.0f * addTime,
	};
	float thanksAmplitude = 4.0f;
	float amplitude[MAXTHANKYOU] =
	{
		0.0f, thanksAmplitude, thanksAmplitude,
		thanksAmplitude, thanksAmplitude, thanksAmplitude,
		thanksAmplitude, thanksAmplitude, thanksAmplitude,
		thanksAmplitude, thanksAmplitude, thanksAmplitude,

	};
	Model* textModel_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;
	TitlePlayer* titlePlayer_ = nullptr;
	GameClearText* clearText_ = nullptr;
	std::list<GameClearText*> gameClearTexts;
	bool finished_ = false;
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;
	int clicks_ = 0;
	int desyncSin = 0;
	enum class Phase
	{
		kFadeIn,
		kMain,
		kFadeOut,
	};

	Phase phase_ = Phase::kFadeIn;

};

