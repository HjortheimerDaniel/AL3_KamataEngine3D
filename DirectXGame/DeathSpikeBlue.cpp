#include "DeathSpikeBlue.h"
#include "MapChipField.h"
#include "functions.h"
#include "cassert"

DeathSpikeBlue::DeathSpikeBlue()
{
}

DeathSpikeBlue::~DeathSpikeBlue()
{
}

void DeathSpikeBlue::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.translation_.y += 0.6f;
	worldTransform_.scale_.x = 0.7f;
	velocity_ = { -kWalkspeed, 0,0 };
}

void DeathSpikeBlue::Update()
{
	worldTransform_.translation_ += velocity_;
	worldTransform_.rotation_.y += 0.2f;
	MapChipCollision();
	Rotation();
	worldTransform_.UpdateMatrix();
}

Vector3 DeathSpikeBlue::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB DeathSpikeBlue::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = { worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f };

	return aabb;
}

void DeathSpikeBlue::CollisionLeft(CollisionMapInfo& info)
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

void DeathSpikeBlue::CollisionRight(CollisionMapInfo& info)
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

void DeathSpikeBlue::NoBlockAheadLeft(CollisionMapInfo& info)
{
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); i++)
	{
		positionsNew[i] = CornerPositon(worldTransform_.translation_ + info.movement, static_cast<Corner>(i));
	}

	// Initialize the hitRightWall flag to false at the beginning
	isNothingLeft_ = false;

	// Always perform the collision check, regardless of movement direction
	MapChipType mapChipType;
	bool nothingLeft = false;
	IndexSet indexSet;

	//indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop] + Vector3(kAdjustWall, 0, 0));
	//mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex +1);
	//if (mapChipType == MapChipType::kBlank)
	//{
	//	nothingLeft = true;
	//}

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlank)
	{
		nothingLeft = true;
	}

	if (nothingLeft)
	{
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(info.movement.y);
		Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		isNothingLeft_ = true;
	}
}

void DeathSpikeBlue::NoBlockAheadRight(CollisionMapInfo& info)
{
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); i++)
	{
		positionsNew[i] = CornerPositon(worldTransform_.translation_ + info.movement, static_cast<Corner>(i));
	}

	// Initialize the hitRightWall flag to false at the beginning
	isNothingRight_ = false;

	// Always perform the collision check, regardless of movement direction
	MapChipType mapChipType;
	bool nothingRight = false;
	IndexSet indexSet;

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlank)
	{
		nothingRight = true;
	}

	if (nothingRight)
	{
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(info.movement.y);
		Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		isNothingRight_ = true;
	}
}

void DeathSpikeBlue::MapChipCollision()
{
	CollisionMapInfo collisionMapInfo;
	collisionMapInfo.movement = velocity_;

	CollisionLeft(collisionMapInfo);
	CollisionRight(collisionMapInfo);
	NoBlockAheadLeft(collisionMapInfo);
	NoBlockAheadRight(collisionMapInfo);
}

void DeathSpikeBlue::Rotation()
{
	if (hitRightWall || isNothingRight_)
	{
		velocity_.x = -kWalkspeed;
	}

	if (hitLeftWall || isNothingLeft_)
	{
		velocity_.x = kWalkspeed;
	}

}

Vector3 DeathSpikeBlue::CornerPositon(const Vector3& center, Corner corner)
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

void DeathSpikeBlue::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);

}

