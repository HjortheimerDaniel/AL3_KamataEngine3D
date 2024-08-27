#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "struct.h"

class Player;
class MapChipField;

class Checkpoint
{
public:
	Checkpoint();

	~Checkpoint();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void Spin();

	void SpinSpeed();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	void OnCollision(const Player* player);

	void OnCollisionFirst(const Player* player);

	bool GetHasBeenTouchedPoint1() { return hasBeenTouchedPoint1; };

	bool GetHasBeenTouched() { return hasBeenTouched_; };

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	static inline const float kWidth = 1.8f;
	static inline const float kHeight = 5.4f;
	bool hasBeenTouchedPoint1 = false;
	bool hasBeenTouched_ = false;
	float maxSpin = 125.5f;
	float spinSpeed = 1.7f;
};

