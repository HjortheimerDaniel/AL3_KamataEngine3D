#include "Checkpoint.h"
#include "MapChipField.h"
#include "functions.h"
#include "cassert"
#include "imgui.h"

Checkpoint::Checkpoint()
{
}

Checkpoint::~Checkpoint()
{
}

void Checkpoint::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.translation_.z = 1.0f;
}

void Checkpoint::Update()
{
	ImGui::Begin("spin");
	ImGui::Text("%f", worldTransform_.rotation_.y);
	ImGui::End();
	worldTransform_.UpdateMatrix();
	Spin();
}

Vector3 Checkpoint::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Checkpoint::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = { worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f };

	return aabb;
}

void Checkpoint::Spin()
{
	if ((hasBeenTouched_ || hasBeenTouchedPoint1) && worldTransform_.rotation_.y < maxSpin)
	{
		worldTransform_.rotation_.y += spinSpeed;
	}

	if (worldTransform_.rotation_.y >= maxSpin)
	{
		worldTransform_.rotation_.y = maxSpin;
	}

	if (worldTransform_.rotation_.y == maxSpin) 
	{
		hasBeenTouched_ = false;
		hasBeenTouchedPoint1 = false;
		worldTransform_.rotation_.y = 0.0f;
	}
	SpinSpeed();
	
}

void Checkpoint::SpinSpeed()
{
	if (worldTransform_.rotation_.y <= 30)
	{
		spinSpeed = 1.7f;
	}
	else if (worldTransform_.rotation_.y >= 30 && worldTransform_.rotation_.y <= 50)
	{
		spinSpeed = 1.5f;
	}
	else if (worldTransform_.rotation_.y >= 50 && worldTransform_.rotation_.y <= 70)
	{
		spinSpeed = 1.3f;
	}
	else if (worldTransform_.rotation_.y >= 70 && worldTransform_.rotation_.y <= 90)
	{
		spinSpeed = 1.1f;
	}
	else if (worldTransform_.rotation_.y >= 90 && worldTransform_.rotation_.y <= 110)
	{
		spinSpeed = 0.8f;
	}
	else if (worldTransform_.rotation_.y >= 110 && worldTransform_.rotation_.y <= 130)
	{
		spinSpeed = 0.6f;
	}
	else if (worldTransform_.rotation_.y >= 130 && worldTransform_.rotation_.y <= 150)
	{
		spinSpeed = 0.4f;
	}
}

void Checkpoint::OnCollision(const Player* player)
{
	(void)player;
	hasBeenTouched_ = true;
}

void Checkpoint::OnCollisionFirst(const Player* player)
{
	(void)player;
	hasBeenTouchedPoint1 = true;
}

void Checkpoint::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
