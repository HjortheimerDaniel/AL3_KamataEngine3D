#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include <numbers>
#include "Windows.h"


class Enemy
{
public:

	Enemy();

	~Enemy();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	//void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };


	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

};

