#include "Enemy.h"
#include "MapChipField.h"
#include "functions.h"

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

	velocity_ = { -kWalkspeed * reverseWalk, 0,0 };
	walkTimer_ = 0.0f;
	isDead = false;

}

void Enemy::Update()
{
	if(!isDead)
	{
		Walk();
		MapChipCollision();
		Rotation();
	} 

	if (isDead) 
	{
		Dead();
	}
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

void Enemy::Walk()
{
	if (canMove_)
	{
		worldTransform_.translation_ += velocity_;
		walkTimer_ += 6.0f / 60.0f; //the speed it rotates
		float param = std::sin(walkTimer_);
		float radian = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f; //make it less aggresive
		worldTransform_.rotation_.z = std::sin(radian);
	}
}

void Enemy::Dead()
{
	if (worldTransform_.scale_.y >= 0.0f) 
	{
		worldTransform_.scale_.y -= 0.05f;
		worldTransform_.scale_.z -= 0.05f;
		worldTransform_.translation_.y -= 0.07f;

	}
}

void Enemy::CollisionLeft(CollisionMapInfo& info)
{
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); i++)
	{
		positionsNew[i] = CornerPositon(worldTransform_.translation_ + info.movement, static_cast<Corner>(i));
	}

	hitLeftWall = false;


	MapChipType mapChipType;
	bool hit = false;
	IndexSet indexSet;

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop] + Vector3(-kAdjustWall, 0, 0));
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex - 1);
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}


	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom] + Vector3(-kAdjustWall, 0, 0));
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex - 1);
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}


	if (hit)
	{
		
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(info.movement.x);
		//Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.isHittingLeftWall = true;
		if (info.movement.x < 0) // Only set movement to 0 if moving left
		{
			hitLeftWall = true;
			hitRightWall = false;

		}
	}
	else
	{
		info.isHittingLeftWall = false;
	}
}

void Enemy::CollisionRight(CollisionMapInfo& info)
{
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); i++)
	{
		positionsNew[i] = CornerPositon(worldTransform_.translation_ + info.movement, static_cast<Corner>(i));
	}

	// Initialize the hitRightWall flag to false at the beginning
	hitRightWall = false;

	// Always perform the collision check, regardless of movement direction
	MapChipType mapChipType;
	bool hit = false;
	IndexSet indexSet;

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop] + Vector3(kAdjustWall, 0, 0));
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex - 1);
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom] + Vector3(kAdjustWall, 0, 0));
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex - 1);
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}

	if (hit)
	{
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(info.movement.x);
		Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.isHittingRightWall = true;
		if (info.movement.x > 0) // Only set movement to 0 if moving right
		{
			hitRightWall = true;
			hitLeftWall = false;
		}
	}
	else
	{
		info.isHittingRightWall = false;
	}
}

void Enemy::MapChipCollision()
{
	CollisionMapInfo collisionMapInfo;
	collisionMapInfo.movement = velocity_;

	CollisionLeft(collisionMapInfo);
	CollisionRight(collisionMapInfo);
}

void Enemy::Rotation()
{
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;


		float destinationRotationYTable[] = {
			-std::numbers::pi_v<float> / 1.1f, // Facing left
			0.0f                              // Facing right
		};

		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		// Normalize angles
		turnFirstRotationY_ = NormalizeAngle(turnFirstRotationY_);
		destinationRotationY = NormalizeAngle(destinationRotationY);

		// Calculate the shortest angle difference
		float angleDiff = AngleDifference(turnFirstRotationY_, destinationRotationY);

		// Interpolate the rotation using easing
		worldTransform_.rotation_.y = EaseInSine(kTimeTurn - turnTimer_, turnFirstRotationY_, turnFirstRotationY_ + angleDiff, kTimeTurn);
	}

	if (hitRightWall)
	{
		velocity_.x = -kWalkspeed;
		if (lrDirection_ != LRDirection::kLeft) // if were moving left and were not facing left
		{
			turnFirstRotationY_ = -worldTransform_.rotation_.y; // set to current rotation
			turnTimer_ = kTimeTurn; // reset the timer
			lrDirection_ = LRDirection::kLeft; // face left
		}
	}

	if (hitLeftWall)
	{
		velocity_.x = kWalkspeed;

		if (lrDirection_ != LRDirection::kRight) // if were moving right and were not facing right
		{
			turnFirstRotationY_ = -worldTransform_.rotation_.y; // set to current rotation
			turnTimer_ = kTimeTurn; // reset the timer
			lrDirection_ = LRDirection::kRight; // face right
		}
	}

}

Vector3 Enemy::CornerPositon(const Vector3& center, Corner corner)
{
	Vector3 offsetTable[kNumCorner] =
	{
		{kWidth / 2.0f, -kHeight / 2.0f, 0}, //Right bottom
		{-kWidth / 2.0f, -kHeight / 2.0f, 0}, //Left bottom
		{kWidth / 2.0f, +kHeight / 2.0f, 0}, //Right top
		{-kWidth / 2.0f, +kHeight / 2.0f, 0}, //Right bottom

	};
	return center + offsetTable[static_cast<uint32_t>(corner)];
}

void Enemy::OnCollision(const Player* player)
{
	(void)player;
}

void Enemy::StompCollision(const Player* player)
{
	(void)player;
	isDead = true;

}

void Enemy::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);

}
