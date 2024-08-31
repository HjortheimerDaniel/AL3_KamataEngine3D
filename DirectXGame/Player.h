#pragma once
#define NOMINMAX
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include <numbers>
#include "Input.h"
#include "algorithm"
#include <iostream>
#include "Windows.h"
#include "struct.h"



class MapChipField;

class Enemy;

class GameScene;

class Goal;

class Spikes;

class Wind;

class Checkpoint;

class ReverseCubes;

class Spring;

class DeathSpikeBlue;

class Player
{
	public:

		Player();

		~Player();

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 移動
		/// </summary>
		void Movement();

		void Rotation();

		WorldTransform& GetWorldTransform() { return worldTransform_; };

		const Vector3& GetVelocity() const { return velocity_; };

		//get info on the the mapchip
		void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

		void CollisionCeiling(CollisionMapInfo& info);

		void CollisionFalling(CollisionMapInfo& info);

		void CollisionRight(CollisionMapInfo& info);

		void CollisionLeft(CollisionMapInfo& info);

		Vector3 CornerPositon(const Vector3& center, Corner corner);

		void AfterCollision(const CollisionMapInfo& info);

		void HitCeiling(const CollisionMapInfo& info);

		Vector3 GetWorldPosition();

		AABB GetAABB();

		void FellBelowStage();

		void OnCollision(const Enemy* enemy);

		void OnCollision(const Spikes* spike);

		void OnCollision(const Wind* wind);

		void OnCollision(const Checkpoint* checkpoint);

		void OnCollision(const ReverseCubes* reverseCubes);

		void OnCollision(const Spring* spring);

		void OnCollision(const DeathSpikeBlue* deathSpikeBlue);

		void OnCollisionGoal(const Goal* goal);
		
		void StompCollision(const Enemy* enemy);

		bool GetIsDead() const { return isDead_; };

		bool GetOnGround() { return onGround_; };

		void SetFallSpeed(float fallSpeed) { kLimitFallSpeed = fallSpeed; };

		float GetLimitFallSpeed() { return kLimitFallSpeed; };

		void SetReversed(bool reverse) { reverse_ = reverse; };

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();


	private:

		WorldTransform worldTransform_;
		Model* model_ = nullptr;
		//uint32_t textureHandle_ = 0u;
		ViewProjection* viewProjection_ = nullptr;
		MapChipField* mapChipField_ = nullptr;
		Vector3 velocity_ = {};


		//rotate the character when we face a new direction
		static inline const float kAcceleration = 0.1f; //movement for frame
		static inline const float kAttenuation = 0.3f; 
		static inline const float kLimitRunSpeed = 0.25f; 
		LRDirection lrDirection_ = LRDirection::kRight; //which way are we facing

		//rotation
		float turnFirstRotationY_ = 0.0f;
		float turnTimer_ = 0.0f;
		static inline const float kTimeTurn = 0.3f;

		//are we on the ground
		bool onGround_ = true;
		static inline const float kGravityAcceleration = 0.1f;
		float kLimitFallSpeed = 0.3f; //change this with the parachute
		static inline float kJumpAcceleration = 0.9f;
		static inline const float kStompAcceleration = 1.1f;
		static inline const float kSpringAcceleration = 2.1f;

		//player collision

		static inline const float kWidth = 1.8f;
		static inline const float kHeight = 1.8f;
		static inline const float kBlank = -0.1f;
		static inline const float kAttenuationLanding = 1.0f;
		static inline const float kAdjustLanding = 1.7f;
		static inline const float kAdjustWall = 0.4f;
		static inline const float kAttenuationWall = 0.3f;

		bool hitRightWall = false;
		bool hitLeftWall = false;
		bool isDead_ = false;
		bool holdingSpace = false;

		bool jumpLeeway = false;
		int leewayTimer = 0;
		bool hasJumped = false;
		bool reverse_ = false;



};

