#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	velocity_ = { -kWalkspeed, 0,0 };
	walkTimer_ = 0.0f;

}

void Enemy::Update()
{
	worldTransform_.translation_ += velocity_;
	walkTimer_ += 6.0f / 60.0f; //the speed it rotates
	float param = std::sin(walkTimer_);
	float radian = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f; //make it less aggresive
	worldTransform_.rotation_.z = std::sin(radian);

	worldTransform_.UpdateMatrix();
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Enemy::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = { worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f };

	return aabb;
}

void Enemy::OnCollision(const Player* player)
{
	(void)player;
}

void Enemy::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);

}
