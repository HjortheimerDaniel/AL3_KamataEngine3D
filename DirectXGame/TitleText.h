#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
class TitleText
{
public:

	TitleText();

	~TitleText();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, bool isFloating);

	void Update();

	void Draw();

	float EaseIn(float x);

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	static inline const float titleSize = 8.0f;
	float theta, amplitude;
	bool isFloating_ = false;



};

