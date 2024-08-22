#include "Wind.h"

Wind::Wind()
{
}

Wind::~Wind()
{
}

void Wind::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	startPos = worldTransform_.translation_;
	worldTransform_.scale_.y = scaleY;

}

Vector3 Wind::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Wind::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = { worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth2 / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f };

	return aabb;
}

void Wind::Movement()
{
	worldTransform_.translation_.y += 1.4f;
	if (worldTransform_.translation_.y >= 200.0f) 
	{
		worldTransform_.translation_.y = -45.0f;
	}
}

void Wind::Update()
{
	Movement();
	worldTransform_.UpdateMatrix();
}

void Wind::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);

}
