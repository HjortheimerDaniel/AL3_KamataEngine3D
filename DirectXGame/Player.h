#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include <numbers>
#include "Input.h"
#include "algorithm"
#include <iostream>
#include "Windows.h"
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define NOMINMAX


enum class LRDirection {
	kRight,
	kLeft
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

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();


	private:

		WorldTransform worldTransform_;
		Model* model_ = nullptr;
		//uint32_t textureHandle_ = 0u;
		ViewProjection* viewProjection_ = nullptr;
		Vector3 velocity_ = {};

		//rotate the character when we face a new direction
		static inline const float kAcceleration = 0.1f; //movement for frame
		static inline const float kAttenuation = 0.7f; 
		static inline const float kLimitRunSpeed = 0.9f; 
		LRDirection lrDirection_ = LRDirection::kRight; //which way are we facing
		float turnFirstRotationY_ = 0.0f;
		float turnTimer_ = 0.0f;
		static inline const float kTimeTurn = 0.3f;

		//are we on the ground
		bool onGround_ = true;
		static inline const float kGravityAcceleration = 0.6f;
		static inline const float kLimitFallSpeed = 1.6f;
		static inline const float kJumpAcceleration = 4.0f;


};

