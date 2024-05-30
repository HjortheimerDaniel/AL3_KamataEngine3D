#include "Player.h"
#include "MapChipField.h"
#include "ImGuiManager.h"




Player::Player()
{
}

Player::~Player()
{
//	delete model_;
	
}

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	model_ = model;
	//textureHandle_ = textureHandle; 
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f; //rotate the model, change the way its facing
	
}
void Player::Update()
{
	Movement();
	Rotation();
	//initialize collision
	CollisionMapInfo collisionMapInfo;
	//copy the velocity
	collisionMapInfo.movement = velocity_;

	Collision(collisionMapInfo);
	
	worldTransform_.UpdateMatrix();
	//worldTransform_.TransferMatrix();
	
}
void Player::Movement()
{
	if (onGround_) {
		if (Input::GetInstance()->PushKey(DIK_RIGHT) ||
			Input::GetInstance()->PushKey(DIK_LEFT))
		{

			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT))
			{
				if (velocity_.x < 0.0f) //were not moving to the right
				{
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;

				if (lrDirection_ != LRDirection::kRight) //if were moving right and were not facing right
				{
					turnFirstRotationY_ = -worldTransform_.rotation_.y; // set to current rotation
					turnTimer_ = kTimeTurn; // reset the timer
					lrDirection_ = LRDirection::kRight; //face right

					
				}
			}
			else if (Input::GetInstance()->PushKey(DIK_LEFT))
			{
				if (velocity_.x > 0.0f) //were not moving to the left
				{
					velocity_.x *= (1.0f - kAttenuation);
					if (velocity_.x * velocity_.x < 0.001f)
					{
						velocity_.x = 0;
					}
				}
				acceleration.x -= kAcceleration;

				if (lrDirection_ != LRDirection::kLeft) //if were moving left and were not facing left
				{
					turnFirstRotationY_ = -worldTransform_.rotation_.y; // set to current rotation
					turnTimer_ = kTimeTurn; // reset the timer
					lrDirection_ = LRDirection::kLeft; //face left

					

				}


			}

			//no matter if we press LEFT or RIGHT we pass here

			velocity_.x += acceleration.x; //add movement to our X
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed); //set the limit for the max speed and min speed

			//worldTransform_.translation_.x += velocity_.x;
		}
		else
		{
			velocity_.x *= (1.0f - kAttenuation);
			if (velocity_.x * velocity_.x < 0.001f)
			{
				velocity_.x = 0;
			}
		}
	}
	else {
		velocity_ += Vector3(0, -kGravityAcceleration, 0);

		//velocity_.y += -kGravityAcceleration;
		//velocity_.x = 0;
		//velocity_.z = 0;

		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	if (Input::GetInstance()->PushKey(DIK_UP))
	{
		if (onGround_)
		{
			velocity_ += Vector3(0, kJumpAcceleration, 0);
			onGround_ = false;
		}
	}

	worldTransform_.translation_.y += velocity_.y; //we need to update the new Y pos before were checking the landing, otherwise we will go through the mapchip for a short while
	if (!(worldTransform_.translation_.x >= 70 && velocity_.x > 0
		|| worldTransform_.translation_.x <= 20 && velocity_.x < 0)) {
		worldTransform_.translation_.x += velocity_.x;
	}


	bool landing = false;

	if (velocity_.y < 0)  //if were falling
	{
		if(worldTransform_.translation_.y <= 2.0f) //if were on the mapchip that is on pos 1.0f or below weve hit the ground
		{
			landing = true;
		}
	}

	if(onGround_)
	{
		if(velocity_.y > 0.0f) //if were moving upwards
		{
			onGround_ = false; //we are not on the ground
		}
	}
	else {

		if(landing) //if were landing
		{
			worldTransform_.translation_.y = 2.0f;
			//velocity_.x *= (1.0f - kAttenuation);
			
			velocity_.y = 0.0f;
			onGround_ = true;
		}
	}

}

void Player::Rotation()
{
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;

		
		float destinationRotationYTable[] =
		{
			 1.0f, // Facing right
			std::numbers::pi_v<float> // Facing left
		};

		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		if (destinationRotationY - turnFirstRotationY_ > std::numbers::pi_v<float>) {
			destinationRotationY -= 2.0f * std::numbers::pi_v<float>;
		}
		else if (destinationRotationY - turnFirstRotationY_ < -std::numbers::pi_v<float>) {
			destinationRotationY +=  3.0f / 2.0f * std::numbers::pi_v<float>;
		}

		//float easing = 1 - turnTimer_ / kTimeTurn;
		//float nowRotationY = std::lerp(turnFirstRotationY_, destinationRotationY, easing);

		//worldTransform_.rotation_.y = destinationRotationY;
		worldTransform_.rotation_.y = EaseInSine(turnTimer_, turnFirstRotationY_, destinationRotationY, kTimeTurn);
	}

#pragma region Better rotation?

	//if (turnTimer_ > 0.0f) {
	//	turnTimer_ -= 1.0f / 60.0f;


	//	float destinationRotationYTable[] =
	//	{
	//		 std::numbers::pi_v < float> / 2.0f, // Facing right
	//		std::numbers::pi_v<float> *3.0f / 2.0f // Facing left
	//	};

	//	float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
	//	if (destinationRotationY - turnFirstRotationY_ > std::numbers::pi_v<float>) {
	//		destinationRotationY -= 2.0f * std::numbers::pi_v<float>;
	//	}
	//	else if (destinationRotationY - turnFirstRotationY_ < -std::numbers::pi_v<float>) {
	//		destinationRotationY += 3.0f / 2.0f * std::numbers::pi_v<float>;
	//	}

	//	float easing = 1 - turnTimer_ / kTimeTurn;
	//	float nowRotationY = std::lerp(turnFirstRotationY_, destinationRotationY, easing);

	//	//worldTransform_.rotation_.y = destinationRotationY;
	//	worldTransform_.rotation_.y = nowRotationY;

#pragma endregion
}

float Player::EaseInOut(float x)
{
	float pi = std::numbers::pi_v<float>;
	return -(cosf(pi * x) - 1) / 2;
}

float Player::EaseInSine(float frameX, float startX, float endX, float endFrameX)
{
	float t = frameX / endFrameX; // Normalize the frameX to [0, 1]
	float easedT = EaseInOut(t);
	return startX + easedT * (endX - startX);
}

void Player::Collision(CollisionMapInfo& info)
{
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); i++)
	{
		positionsNew[i] = CornerPositon(worldTransform_.translation_ + info.movement, static_cast<Corner>(i));
	}

	if(info.movement.y <= 0)
	{
		return;
	}

	MapChipType mapChipType;
	bool hit = false;
	IndexSet indexSet;
	
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) 
	{
		hit = true;
	}

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock)
	{
		hit = true;
	}

	if (hit)
	{
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
		Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.movement.y = std::max(0.0f, (float)indexSet.yIndex);
		info.isHittingCeiling = true;
	}
}

Vector3 Player::CornerPositon(const Vector3& center, Corner corner)
{
	/*if (corner == kRightBottom)
	{
		return center + kWidth / 2.0f, -kHeight / 2.0f, 0;
	} 
	else if (corner == kLeftBottom)
	{
		return center + -kWidth / 2.0f, -kHeight / 2.0f, 0;
	} 
	else if(corner == kRightTop)
	{
		return center + kWidth / 2.0f, kHeight / 2.0f, 0;
	}
	else
	{
		return center + -kWidth / 2.0f, kHeight / 2.0f, 0;
	}*/

	//SAME AS ABOVE

	Vector3 offsetTable[kNumCorner] =
	{
		{kWidth / 2.0f, -kHeight / 2.0f, 0}, //Right bottom
		{-kWidth / 2.0f, -kHeight / 2.0f, 0}, //Left bottom
		{kWidth / 2.0f, +kHeight / 2.0f, 0}, //Right top
		{-kWidth / 2.0f, +kHeight / 2.0f, 0}, //Right bottom

	};
	return center + offsetTable[static_cast<uint32_t>(corner)];

}

void Player::AfterCollision(const CollisionMapInfo& info)
{
	worldTransform_.translation_ += info.movement;
}

void Player::HitCeiling(const CollisionMapInfo& info)
{
	if(info.isHittingCeiling)
	{
		ImGui::Text("hit ceiling");
		velocity_.y = 0;
	}
}

void Player::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

;
