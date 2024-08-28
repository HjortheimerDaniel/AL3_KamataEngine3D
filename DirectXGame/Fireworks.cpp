#include "Fireworks.h"
#include "algorithm"

Fireworks::Fireworks()
{
}

Fireworks::~Fireworks()
{
}

void Fireworks::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, Vector4 color, int startUpdate)
{
	assert(model);
	model_ = model;
	//textureHandle_ = textureHandle; 
	viewProjection_ = viewProjection;
	for (auto& worldTransform : worldTransforms_)
	{
		worldTransform.Initialize();
		worldTransform.translation_ = position;
		//worldTransform.rotation_ = { 10.f,10.f,10.0f };
		
	}
	startPos_ = position;
	objectColor_.Initialize();
	color_ = color; //{ 0,1,1,1 };
	particleFade_ = 1;
	startUpdate_ = startUpdate;

}

void Fireworks::Update()
{
	if (updateTimer_ < startUpdate_)
	{
		updateTimer_++;
	}
	if (updateTimer_ >= startUpdate_)
	{
		startUpdate_ = updateTimer_;
		isUpdate = true;

	}
	if (isUpdate)
	{


		counter_ += 1.0f / 60.0f;
		if (counter_ >= kDuration)
		{

			counter_ = kDuration;
		}

		/*if (isFinished_)
		{
			return;
		}*/

		for (int i = 0; i < kNumParticles; i++)
		{
			worldTransforms_[i].matWorld_ = MakeAffineMatrix(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);
			worldTransforms_[i].TransferMatrix();
			worldTransforms_[i].UpdateMatrix();
		}

		particleFade_ -= 0.01f;

		ParticleMovement();
		ParticleFade();
		ResetFireWorks();
	}
}

void Fireworks::ParticleMovement()
{
	for (uint32_t i = 0; i < kNumParticles; i++)
	{
		Vector3 velocity = { kSpeed, 0,0 };
		float angle = kAngleUnit * i;
		Matrix4x4 matrixRotation = MakeRotateMatrixZ(angle);
		velocity = Transform(velocity, matrixRotation);
		worldTransforms_[i].translation_ += velocity;
		//worldTransforms_[i].rotation_.z = velocity.z;
		Vector3 direction = Normalize(velocity);
		float rotationAngle = atan2(direction.y, direction.x);
		worldTransforms_[i].rotation_.z = rotationAngle;
	}
}

void Fireworks::ResetFireWorks()
{
	
	if (particleFade_ <= 0.0f)
	{
		particleFade_ = 0.0f;
		startReset_ = true;
	} 
	else 
	{
		startReset_ = false;
	}

	if (startReset_)
	{
		resetTimer_++;
	}

	if (resetTimer_ >= 60) 
	{	
		reset_ = true;

		resetTimer_ = 0;
		Initialize(model_, viewProjection_, startPos_, color_, startUpdate_);
	}
	else 
	{
		reset_ = false;
	}

}

void Fireworks::ParticleFade()
{
	color_.w = std::clamp(particleFade_, 0.0f, 1.0f);
	objectColor_.SetColor(color_);
	objectColor_.TransferMatrix();
}

void Fireworks::Draw()
{
	/*if (isFinished_)
	{
		return;
	}*/

	for (auto& worldTransform : worldTransforms_)
	{
		model_->Draw(worldTransform, *viewProjection_, &objectColor_);
	}
}
