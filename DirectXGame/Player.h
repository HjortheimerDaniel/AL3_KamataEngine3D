#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include <numbers>
#include "Input.h"
#include "algorithm"



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

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();


	private:

		WorldTransform worldTransform_;
		Model* model_ = nullptr;
		uint32_t textureHandle_ = 0u;
		ViewProjection* viewProjection_ = nullptr;
		Vector3 velocity_ = {};
		static inline const float kAcceleration = 0.1f; //movement for frame
		static inline const float kAttenuation = 0.7f; 
		static inline const float kLimitRunSpeed = 1.0f; 


};

