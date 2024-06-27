#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <array>
#include "cassert"
#define _USE_MATH_DEFINES
#include <math.h>



class DeathParticles
{
public:


	DeathParticles();

	~DeathParticles();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void ParticleMovement();

	void ParticleFade();

	void Draw();

private:

	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_;
	static inline const uint32_t kNumParticles = 8; //amount of particles
	std::array<WorldTransform, kNumParticles> worldTransforms_;
	//std::vector<WorldTransform*>worldTransformParticles_;

	static inline const float kDuration = 1.4f; 
	static inline const float kSpeed = 0.2f; 
	static inline const float kAngleUnit = (float(M_PI) *2) / kNumParticles;
	bool isFinished_ = false;
	float counter_ = 0.0f;
	ObjectColor objectColor_;
	Vector4 color_;
	float particleFade_;
};

