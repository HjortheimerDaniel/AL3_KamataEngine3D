#include "Player.h"


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
					lrDirection_ = LRDirection::kRight; //face right

					turnFirstRotationY_ = -worldTransform_.rotation_.y; // set to current rotation
					turnTimer_ = kTimeTurn; // reset the timer


				}



			}
			else if (Input::GetInstance()->PushKey(DIK_LEFT))
			{
				if (velocity_.x > 0.0f) //were not moving to the left
				{
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;

				if (lrDirection_ != LRDirection::kLeft) //if were moving left and were not facing left
				{
					lrDirection_ = LRDirection::kLeft; //face left

					turnFirstRotationY_ = -worldTransform_.rotation_.y; // set to current rotation
					turnTimer_ = kTimeTurn; // reset the timer

				}


			}

			//no matter if we press LEFT or RIGHT we pass here


			velocity_.x += acceleration.x;
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed); //set the limit for the max speed and min speed

			worldTransform_.translation_.x += velocity_.x;

		}
		else
		{
			velocity_.x *= (1.0f - kAttenuation);

		}
	}
	else {
		velocity_ += Vector3(0, -kGravityAcceleration, 0);

		//velocity_.y += -kGravityAcceleration;
		//velocity_.x = 0;
		//velocity_.z = 0;

		velocity_.y = max(velocity_.y, -kLimitFallSpeed);
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
			velocity_.x *= (1.0f - 0.3f);
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
			destinationRotationY += 2.0f * std::numbers::pi_v<float>;
		}
		//worldTransform_.rotation_.y = destinationRotationY;
		worldTransform_.rotation_.y = EaseInSine(turnTimer_, turnFirstRotationY_, destinationRotationY, kTimeTurn);
	}
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

void Player::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

;
