#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
class TitleText
{
public:

	TitleText();

	~TitleText();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	static inline const float titleSize = 6.0f;

};

