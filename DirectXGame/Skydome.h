#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "assert.h"

class Skydome
{

	public:

		Skydome();

		~Skydome();

		void Initialize(Model* model, ViewProjection* viewProjection);

		void Update();

		void Draw();


	private:

		WorldTransform worldTransform_;
		Model* model_ = nullptr;
		ViewProjection* viewProjection_ = nullptr;
				
};

