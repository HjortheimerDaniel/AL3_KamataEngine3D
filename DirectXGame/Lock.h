#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "struct.h"

class MapChipField;

class Lock
{
public:

	Lock();

	~Lock();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	static inline const float kWidth = 8.8f;
	static inline const float kHeight = 2.0f;
	bool isKeyTaken = true;
};

