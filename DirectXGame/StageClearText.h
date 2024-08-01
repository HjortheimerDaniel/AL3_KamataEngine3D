#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"

class StageClearText
{
public:

	StageClearText();

	~StageClearText();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	float EaseIn(float x);

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	static inline const float titleSize = 8.0f;
	float theta, amplitude;

};

