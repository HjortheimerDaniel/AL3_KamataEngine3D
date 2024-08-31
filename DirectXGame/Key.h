#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "struct.h"

class Player;

class MapChipField;

class Key
{
public:

	Key();

	~Key();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	void OnCollision(const Player* player);

	bool GetIsKeyTaken() { return isKeyTaken; };

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	static inline const float kWidth = 1.8f;
	static inline const float kHeight = 1.8f;
	bool isKeyTaken = false;
};

