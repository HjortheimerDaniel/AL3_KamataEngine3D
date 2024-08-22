#include "Spikes.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "algorithm"
#include <numbers>

Spikes::Spikes()
{
}

Spikes::~Spikes()
{
}

void Spikes::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	startPos = worldTransform_.translation_;
	spikeStruct_ = SpikesStruct::Active;

}

void Spikes::Update()
{
	if(move_)
	{
		MovingSpikes();

	}
	if (rotateUpDown_) 
	{
		RotateSpikeUpsideDown();
	}
	if (rotateRight_) 
	{
		RotateSpike90Degrees();
	}
	if (moveRight_ && mayMove_) 
	{
		MovingSpikesRight();
	}
	SpikeState();
	worldTransform_.UpdateMatrix();
}

void Spikes::SpikeTimer()
{
	spikeTimer++; //Add this for movement
}

void Spikes::SpikeState()
{
	switch (spikeStruct_)
	{
	case SpikesStruct::Inactive:
		if (spikeTimer >= spikeMaxTimer)
		{
			spikeTimer = 0;
			spikeStruct_ = SpikesStruct::Awake;
		}
		break;
	case SpikesStruct::Awake:
		if (spikeTimer == 1) 
		{
			worldTransform_.translation_.y = worldTransform_.translation_.y + 0.5f;
		}
		if (spikeTimer >= spikeMaxTimer)
		{
			spikeTimer = 0;
			spikeStruct_ = SpikesStruct::Active;
		}

		break;
	case SpikesStruct::Active:
		if (spikeTimer == 1) 
		{
			worldTransform_.translation_.y = worldTransform_.translation_.y + 1.3f;

		}
		if (spikeTimer >= spikeMaxTimer)
		{
			spikeTimer = 0;
			spikeStruct_ = SpikesStruct::Return;
		}

		break;
	case SpikesStruct::Return:
		//worldTransform_.translation_.y = worldTransform_.translation_.y - 0.2f;
		if (worldTransform_.translation_.y >= startPos.y) 
		{
			worldTransform_.translation_.y -= 0.1f;

		}
		/*if (spikeTimer % 10 == 0) 
		{
			worldTransform_.translation_.y -= 0.1f;
		}*/
		if (spikeTimer >= spikeMaxTimer)
		{
			spikeTimer = 0;
			spikeStruct_ = SpikesStruct::Inactive;
		}
		break;

	default:
		break;
	}
}

void Spikes::RotateSpikeUpsideDown()
{
	worldTransform_.rotation_.z = 1.0f * std::numbers::pi_v<float>;
}

void Spikes::RotateSpike90Degrees()
{
	worldTransform_.rotation_.z = 1.5f * std::numbers::pi_v<float>;

}

void Spikes::MovingSpikes()
{
	theta += float(M_PI) / 70.0f;
	worldTransform_.translation_.x = cosf(theta) * amplitude_ + movingStartPosition;

}

void Spikes::MovingSpikesRight()
{
	if(worldTransform_.translation_.x <= 108)
	{
		worldTransform_.translation_.x += 0.8f;
	}
}

Vector3 Spikes::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Spikes::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = { worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f };
	
	return aabb;
	
	
}

void Spikes::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
