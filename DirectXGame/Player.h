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


class MapChipField;

enum class LRDirection 
{
	kRight,
	kLeft
};

struct CollisionMapInfo
{
	bool isHittingCeiling = false;
	bool isOnFloor;
	bool isHittingWall;
	Vector3 movement;
};

enum Corner
{
	kRightBottom,
	kLeftBottom,
	kRightTop,
	kLeftTop,
	kNumCorner
};

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

		float EaseInOut(float x);

		float EaseInSine(float frameX, float startX, float endX, float endFrameX);

		WorldTransform& GetWorldTransform() { return worldTransform_; };

		const Vector3& GetVelocity() const { return velocity_; };

		//get info on the the mapchip
		void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

		void Collision(CollisionMapInfo& info);

		Vector3 CornerPositon(const Vector3& center, Corner corner);

		void AfterCollision(const CollisionMapInfo& info);

		void HitCeiling(const CollisionMapInfo& info);

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
		static inline const float kAttenuation = 0.7f; 
		static inline const float kLimitRunSpeed = 0.6f; 
		LRDirection lrDirection_ = LRDirection::kRight; //which way are we facing

		//rotation
		float turnFirstRotationY_ = 0.0f;
		float turnTimer_ = 0.0f;
		static inline const float kTimeTurn = 0.3f;

		//are we on the ground
		bool onGround_ = true;
		static inline const float kGravityAcceleration = 0.2f;
		static inline const float kLimitFallSpeed = 0.3f;
		static inline const float kJumpAcceleration = 1.3f;

		//player collision

		static inline const float kWidth = 1.8f;
		static inline const float kHeight = 1.8f;
		static inline const float kBlank = 0.1f;

};

