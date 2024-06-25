#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <array>
#include "cassert"



class DeathParticles
{
public:


	DeathParticles();

	~DeathParticles();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

private:

	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_;
	static inline const uint32_t kNumParticles = 8; //amount of particles
	std::array<WorldTransform, kNumParticles> worldTransforms_;
	std::vector<WorldTransform*>worldTransformParticles_;

};

