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

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	void Update();

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	static inline const float titleSize = 1.0f;
	//float theta, amplitude;

};

