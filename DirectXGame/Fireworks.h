#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <array>
#include "cassert"
#define _USE_MATH_DEFINES
#include <math.h>

class Fireworks
{
public:
	Fireworks();

	~Fireworks();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, const Vector4 color, int startUpdate);

	void Update();

	void ParticleMovement();

	void ResetFireWorks();

	void ParticleFade();

	bool GetReset() { return reset_; };

	//bool GetIsFinished() const { return isFinished_; };

	void Draw();

private:

	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_;
	static inline const uint32_t kNumParticles = 8; //amount of particles
	std::array<WorldTransform, kNumParticles> worldTransforms_;
	static inline const float kDuration = 0.4f;
	static inline const float kSpeed = 0.4f;
	static inline const float kAngleUnit = (float(M_PI) * 2) / kNumParticles;
	Vector3 startPos_;
	bool reset_ = false;
	int resetTimer_ = 0;
	bool startReset_ = false;
	//bool isFinished_ = false;
	float counter_ = 0.0f;
	ObjectColor objectColor_;
	Vector4 color_;
	float particleFade_;
	bool finished_ = false;
	int startUpdate_ = 0;
	int updateTimer_ = 0;
	bool isUpdate = false;

};

