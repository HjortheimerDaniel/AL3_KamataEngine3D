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

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	void Movement();

	void Update();

	void Draw();


private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	Vector3 startPos;
	static inline const float kWidth = 18.0f;
	static inline const float kWidth2 = 28.0f;
	static inline const float kHeight = 120.0f;
	float scaleY = 3.0f;
};

