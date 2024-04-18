#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Player
{
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();


	private:

		WorldTransform worldTransform_;
		Model* model_ = nullptr;
		uint32_t textureHandle_ = 0u;


};

