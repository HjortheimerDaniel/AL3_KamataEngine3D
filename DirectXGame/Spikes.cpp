#include "Spikes.h"

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

}

void Spikes::Update()
{
	spikeTimer++;
	SpikeMovement();
	worldTransform_.UpdateMatrix();
}

void Spikes::SpikeMovement()
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
