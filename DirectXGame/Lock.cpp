#include "Lock.h"
#include "MapChipField.h"
#include "functions.h"
#include "cassert"

Lock::Lock()
{
}

Lock::~Lock()
{
}

void Lock::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Lock::Update()
{
	worldTransform_.UpdateMatrix();
}

Vector3 Lock::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Lock::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = { worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f };

	return aabb;
}



void Lock::Draw()
{
	if (!isKeyTaken) 
	{
		model_->Draw(worldTransform_, *viewProjection_);
	}

}