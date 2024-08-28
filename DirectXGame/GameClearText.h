#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"

class GameClearText
{
public:

	GameClearText();

	~GameClearText();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, float startpos, float startUpdate, float amplitude);

	void Update();

	void Draw();

	

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	static inline const float titleSize = 8.0f;
	float theta, amplitude_;
	float startpos_;
	float updateTimer_;
	float startUpdate_;
};

