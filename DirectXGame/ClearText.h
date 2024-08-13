#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MapChipField.h"
#include "cassert"

class ClearText
{
public:


	ClearText();

	~ClearText();

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
	int timer = 0;


};

