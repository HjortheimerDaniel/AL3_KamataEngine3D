#include "DeathParticles.h"
#include "imgui.h"
#include "algorithm"


DeathParticles::DeathParticles()
{
}

DeathParticles::~DeathParticles()
{
}

void DeathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	//textureHandle_ = textureHandle; 
	viewProjection_ = viewProjection;
	for (auto& worldTransform : worldTransforms_ )
	{
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	
	objectColor_.Initialize();
	color_ = { 1,1,1,1 };
	particleFade_ = 1;

}

void DeathParticles::Update()
{
	/*ImGui::Begin("Window");
	ImGui::Text("isFinished %d", isFinished_);
	ImGui::Text("counter %f", counter_);
	ImGui::Text("fade %f", particleFade_);
	ImGui::End();*/
	

	counter_ += 1.0f / 60.0f;
	if (counter_ >= kDuration)
	{
		counter_ = kDuration;
		isFinished_ = true;

	}

	if (isFinished_) 
	{
		return;
	}
	
	for (int i = 0; i < kNumParticles; i++)
	{
		worldTransforms_[i].matWorld_ = MakeAffineMatrix(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);
		worldTransforms_[i].TransferMatrix();
		worldTransforms_[i].UpdateMatrix();
	}
	
	particleFade_ -= 0.01f;
	
	ParticleMovement();
	ParticleFade();
	
	
}

void DeathParticles::ParticleMovement()
{
	for (uint32_t i = 0; i < kNumParticles; i++)
	{
		Vector3 velocity = { kSpeed, 0,0 };
		float angle = kAngleUnit * i;
		Matrix4x4 matrixRotation = MakeRotateMatrixZ(angle);
		velocity = Transform(velocity, matrixRotation);
		worldTransforms_[i].translation_ += velocity;
	}

	
}

void DeathParticles::ParticleFade()
{
	color_.w = std::clamp(particleFade_, 0.0f, 1.0f);
	objectColor_.SetColor(color_);
	objectColor_.TransferMatrix();
}

void DeathParticles::Draw()
{
	if (isFinished_)
	{
		return;
	}

	for (auto& worldTransform : worldTransforms_) 
	{
		model_->Draw(worldTransform, *viewProjection_, &objectColor_);
	}

	/*for (int i = 0; i < kNumParticles; i++)
	{
		model_->Draw(worldTransforms_[i], *viewProjection_);
	}*/
}
