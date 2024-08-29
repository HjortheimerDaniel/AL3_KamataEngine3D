#include "TitlePlayer.h"
#include "imgui.h"

TitlePlayer::TitlePlayer()
{
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position, bool isStage1, bool isMovementBoy, bool isJumpBoy)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	isScene1_ = isStage1;
	isMovementBoy_ = isMovementBoy;
	isJumpBoy_ = isJumpBoy;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = 3.14159265359f / 2;
	worldTransform_.scale_ = { titlePlayerSize, titlePlayerSize, titlePlayerSize };
}

void TitlePlayer::Movement()
{
	Vector3 acceleration = {};
	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {


		if (velocity_.x < 0.0f) // were not moving to the right
		{
			velocity_.x *= (1.0f - kAttenuation);
			if (velocity_.x * velocity_.x < 0.001f)
			{
				velocity_.x = 0;
			}
		}
		if (worldTransform_.translation_.x <= 60) {
			acceleration.x += kAcceleration;
		}
		if (lrDirection_ != LRDirection::kRight) // if were moving right and were not facing right
		{
			lrDirection_ = LRDirection::kRight; // face right
			turnFirstRotationY_ = worldTransform_.rotation_.y; // set to current rotation
			turnTimer_ = kTimeTurn; // reset the timer
		}
	}
	else if (Input::GetInstance()->PushKey(DIK_LEFT))
	{
		if (velocity_.x > 0.0f) // were not moving to the left
		{
			velocity_.x *= (1.0f - kAttenuation);
			if (velocity_.x * velocity_.x < 0.001f)
			{
				velocity_.x = 0;
			}
		}
		if (worldTransform_.translation_.x >= -40) {
			acceleration.x -= kAcceleration;
		}

		if (lrDirection_ != LRDirection::kLeft) // if were moving left and were not facing left
		{
			lrDirection_ = LRDirection::kLeft; // face left
			turnFirstRotationY_ = worldTransform_.rotation_.y; // set to current rotation
			turnTimer_ = kTimeTurn; // reset the timer
		}
	}

	// Update horizontal velocity

	velocity_.x += acceleration.x; // add movement to our X
	velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed); // set the limit for the max speed and min speed

	if (!Input::GetInstance()->PushKey(DIK_RIGHT) && !Input::GetInstance()->PushKey(DIK_LEFT))
	{
		velocity_.x *= (1.0f - kAttenuation);
		if (velocity_.x * velocity_.x < 0.001f)
		{
			velocity_.x = 0;
		}
	}
	if (worldTransform_.translation_.x <= 60 && !Input::GetInstance()->PushKey(DIK_LEFT) || worldTransform_.translation_.x >= -40 && !Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		worldTransform_.translation_.x += velocity_.x;
	}

	if (worldTransform_.translation_.x >= 60) 
	{
		worldTransform_.translation_.x = 60;
	}

	if(worldTransform_.translation_.x <= -40)
	{
		worldTransform_.translation_.x = -40;
	}
}

void TitlePlayer::Rotate()
{
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;


		// Player's Left & Right angle table
		float destinationRotationYTable[] = {
			std::numbers::pi_v<float> / 2.0f,
			std::numbers::pi_v<float> *3.0f / 2.0f,
		};
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		float easing = 1 - turnTimer_ / kTimeTurn;
		float nowRotationY = std::lerp(turnFirstRotationY_, destinationRotationY, easing);
		// Get angle from status
		worldTransform_.rotation_.y = nowRotationY;
	}

}

void TitlePlayer::Jump()
{
	if (Input::GetInstance()->TriggerKey(DIK_UP) && !hasJump)
	{
		hasJump = true;
		velocity_.y = 0.0f;
		//holdingSpace = true;
		velocity_ += Vector3(0, kJumpAcceleration, 0);
	}
	worldTransform_.translation_.y += velocity_.y;
	if (worldTransform_.translation_.y >= -25.0f) 
	{
		velocity_ += Vector3(0, -kGravityAcceleration, 0);
	}
	else 
	{
		worldTransform_.translation_.y = -25.0f;
		hasJump = false;
	}

}

void TitlePlayer::Update()
{
	if (isScene1_) 
	{
		worldTransform_.translation_.x += 1;

		if (worldTransform_.translation_.x >= 150.0f)
		{
			worldTransform_.translation_.x = -100.0f;
		}
	}
	if (isMovementBoy_) 
	{
		Movement();
		Rotate();

	}
	if (isJumpBoy_) 
	{
		Jump();
	}
	worldTransform_.UpdateMatrix();
}

void TitlePlayer::Draw()
{

	model_->Draw(worldTransform_, *viewProjection_);
}
