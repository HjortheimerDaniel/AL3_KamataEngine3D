#include "Key.h"
#include "MapChipField.h"
#include "functions.h"
#include "cassert"

Key::Key()
{
}

Key::~Key()
{
}

void Key::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Key::Update()
{
	worldTransform_.rotation_.y += 0.05f;
	worldTransform_.UpdateMatrix();
}

Vector3 Key::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Key::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = { worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f };

	return aabb;
}



void Key::OnCollision(const Player* player)
{
	(void)player;
	isKeyTaken = true;
}

void Key::Draw()
{
	if (!isKeyTaken)
	{
		model_->Draw(worldTransform_, *viewProjection_);
	}

}
