#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"

class TitlePlayer
{
public:

	TitlePlayer();

	~TitlePlayer();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	static inline const float titlePlayerSize = 3.0f;

};

