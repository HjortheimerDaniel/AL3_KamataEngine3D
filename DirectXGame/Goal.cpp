#include "Goal.h"
#include "MapChipField.h"
#include "functions.h"
#include "cassert"

Goal::Goal()
{
}

Goal::~Goal()
{
}

void Goal::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Goal::Update()
{
	worldTransform_.UpdateMatrix();
}

Vector3 Goal::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Goal::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = { worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f };

	return aabb;
}

void Goal::OnCollision(const Player* player)
{
	(void)player;
	
}

void Goal::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);

}
