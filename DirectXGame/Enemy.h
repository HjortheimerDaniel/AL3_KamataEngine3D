#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include <numbers>
#include "Windows.h"
#include "struct.h"

class Player;


class Enemy
{
public:

	Enemy();

	~Enemy();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	//void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void OnCollision(const Player* player);

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	//MOVEMENT
	static inline const float kWalkspeed = 0.05f; //movement for frame
	Vector3 velocity_ = {};

	//ANIMATION
	static inline const float kWalkMotionAngleStart = 0.05f; //movement for frame
	static inline const float kWalkMotionAngleEnd = 0.3f; //movement for frame
	static inline const float kWalkMotionTime = 0.3f; //movement for frame
	float walkTimer_ = 0.0f;

	static inline const float kWidth = 1.8f;
	static inline const float kHeight = 1.8f;

};

