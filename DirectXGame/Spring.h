#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "struct.h"

class Player;
class MapChipField;

class Spring
{
public:

	Spring();

	~Spring();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	Vector3 GetWorldPosition();

	void ResetScale();

	AABB GetAABB();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	void OnCollision(const Player* player);

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	static inline const float kWidth = 1.8f;
	static inline const float kHeight = 1.8f;
};

