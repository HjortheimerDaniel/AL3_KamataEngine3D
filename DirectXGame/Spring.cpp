#include "Spring.h"
#include "MapChipField.h"
#include "functions.h"
#include "cassert"

Spring::Spring()
{
}

Spring::~Spring()
{
}

void Spring::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.translation_.z = 0.7f;
	worldTransform_.translation_.y -= 0.4f;
	worldTransform_.scale_.y = 2.0f;
}

void Spring::Update()
{
	ResetScale();
	worldTransform_.UpdateMatrix();
}

Vector3 Spring::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Spring::ResetScale()
{
	if (worldTransform_.scale_.y > 2.0f)
	{
		worldTransform_.scale_.y -= 0.5;
	}

	if (worldTransform_.scale_.y < 2.0f)
	{
		worldTransform_.scale_.y = 2.0f;
	}
}

AABB Spring::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = { worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f };

	return aabb;
}

void Spring::OnCollision(const Player* player)
{
	(void)player;
	worldTransform_.scale_.y = 12.5f;

}

void Spring::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);

}
