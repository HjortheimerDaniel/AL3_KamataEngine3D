#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include <numbers>
#include "Windows.h"
#include "struct.h"

class Player;
class MapChipField;



class Enemy
{
public:

	Enemy();

	~Enemy();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	//void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	Vector3 GetWorldPosition();

	bool GetIsDead() { return isDead; };

	AABB GetAABB();

	void Walk();

	void Dead();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	void SetCanMove(bool canMove) { canMove_ = canMove; };

	//void SetIsCollidingLeft(bool isCollidingLeft) {isCollidingLeft_ = isCollidingLeft; };

	//void SetIsCollidingRight(bool isCollidingRight) {isCollidingRight_ = isCollidingRight; };

	void CollisionLeft(CollisionMapInfo& info);

	void CollisionRight(CollisionMapInfo& info);

	void NoBlockAheadLeft(CollisionMapInfo& info);

	void NoBlockAheadRight(CollisionMapInfo& info);

	void MapChipCollision();

	void Rotation();

	Vector3 CornerPositon(const Vector3& center, Corner corner);

	void OnCollision(const Player* player);

	void StompCollision(const Player* player);

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	//MOVEMENT
	static inline const float kWalkspeed = 0.05f; //movement for frame
	float reverseWalk = 1.0f; //movement for frame
	Vector3 velocity_ = {};

	//ANIMATION
	static inline const float kWalkMotionAngleStart = 0.05f; //movement for frame
	static inline const float kWalkMotionAngleEnd = 0.3f; //movement for frame
	static inline const float kWalkMotionTime = 0.3f; //movement for frame
	float walkTimer_ = 0.0f;


	static inline const float kWidth = 1.8f;
	static inline const float kHeight = 1.8f;
	bool isDead = false;
	bool hitLeftWall = false;
	bool hitRightWall = false;
	MapChipField* mapChipField_ = nullptr;
	static inline const float kAdjustWall = 0.4f;

	//rotation
	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;
	static inline const float kTimeTurn = 0.3f;
	LRDirection lrDirection_ = LRDirection::kLeft; //which way are we facing

	//make enemy start moving
	bool canMove_ = false;

	//no block ahead
	bool isNothingLeft_ = false;
	bool isNothingRight_ = false;


};

