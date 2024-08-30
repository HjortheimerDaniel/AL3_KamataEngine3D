#include "ReverseCubes.h"
#include "functions.h"
#include "cassert"

ReverseCubes::ReverseCubes()
{
}

ReverseCubes::~ReverseCubes()
{
	delete reversedCubeModel[0];
	delete reversedCubeModel[1];
}

void ReverseCubes::Initialize(ViewProjection* viewProjection, const Vector3& position, bool isReversedCube)
{
	isReversedCube_ = isReversedCube;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void ReverseCubes::Update()
{
	if (isReversedCube_) 
	{
		model_ = reversedCubeModel[1];
	}
	else 
	{
		model_ = reversedCubeModel[0];

	}
	worldTransform_.UpdateMatrix();
}

Vector3 ReverseCubes::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB ReverseCubes::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = { worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f };

	return aabb;
}

//void ReverseCubes::OnCollision(const Player* player)
//{
//	(void)player;
//
//}

void ReverseCubes::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);

}
