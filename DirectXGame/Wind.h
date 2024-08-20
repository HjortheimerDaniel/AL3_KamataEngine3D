#pragma once
#include "WorldTransform.h"
#include "cassert"
#include "struct.h"
#include "TextureManager.h"
#include "Model.h"

class MapChipField;

class Wind
{
public:

	Wind();

	~Wind();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();


private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	Vector3 startPos;
};

