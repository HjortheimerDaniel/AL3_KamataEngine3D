#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include "struct.h"
#include "Input.h"
#include "algorithm"
#include <numbers>

class TitlePlayer
{
public:

	TitlePlayer();

	~TitlePlayer();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, bool isStage1, bool isMovementBoy, bool isJumpBoy);

	void Movement();

	void Rotate();

	void Jump();

	void Update();

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	static inline const float titlePlayerSize = 3.0f;
	bool isScene1_ = false;
	bool isMovementBoy_ = false;
	bool isJumpBoy_ = false;

	Vector3 velocity_ = {};

	//rotate the character when we face a new direction
	static inline const float kAcceleration = 0.2f; //movement for frame
	static inline const float kAttenuation = 0.1f;
	static inline const float kLimitRunSpeed = 0.95f;
	LRDirection lrDirection_ = LRDirection::kRight; //which way are we facing

	//rotation
	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;
	static inline const float kTimeTurn = 0.3f;

	static inline const float kGravityAcceleration = 0.1f;
	float kLimitFallSpeed = 0.3f; //change this with the parachute
	static inline const float kJumpAcceleration = 1.6f;
	bool hasJump = false;
};

