#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "struct.h"

class MapChipField;


class DeathSpikeBlue
{
public:

	DeathSpikeBlue();

	~DeathSpikeBlue();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	void CollisionLeft(CollisionMapInfo& info);

	void CollisionRight(CollisionMapInfo& info);

	void NoBlockAheadLeft(CollisionMapInfo& info);

	void NoBlockAheadRight(CollisionMapInfo& info);

	void MapChipCollision();

	void Rotation();

	Vector3 CornerPositon(const Vector3& center, Corner corner);


	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	static inline const float kWidth = 5.2f;
	static inline const float kHeight = 5.4f;

	//MOVEMENT
	bool isNothingLeft_ = false;
	bool isNothingRight_ = false;

	bool hitLeftWall = false;
	bool hitRightWall = false;
	static inline const float kAdjustWall = 0.4f;

	Vector3 velocity_ = {};
	static inline const float kWalkspeed = 0.05f;
};

