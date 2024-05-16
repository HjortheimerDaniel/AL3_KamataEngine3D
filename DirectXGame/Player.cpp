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
	//worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();
	Movement();

}
void Player::Movement()
{

	if(Input::GetInstance()->PushKey(DIK_RIGHT) || 
		Input::GetInstance()->PushKey(DIK_LEFT))
	{

		Vector3 acceleration = {};
		if(Input::GetInstance()->PushKey(DIK_RIGHT))
		{
			
		

			if(velocity_.x < 0.0f) //were not moving to the right
			{
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration.x += kAcceleration;

			if (lrDirection_ != LRDirection::kRight) //if were moving right and were not facing right
			{
				lrDirection_ = LRDirection::kRight; //face right

			}

			

		} 
		else if(Input::GetInstance()->PushKey(DIK_LEFT))
		{
			

			if (velocity_.x > 0.0f) //were not moving to the left
			{
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration.x -= kAcceleration;

			if (lrDirection_ != LRDirection::kLeft) //if were moving left and were not facing left
			{
				lrDirection_ = LRDirection::kLeft; //face left
			}


		}
		
		//no matter if we press LEFT or RIGHT we pass here


		velocity_.x += acceleration.x; 
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed); //set the limit for the max speed and min speed

		worldTransform_.translation_.x += velocity_.x;

		Rotation();
		
	}
	else 
	{
		velocity_.x *= (1.0f - kAttenuation);
		
	}
	
	

}
void Player::Rotation()
{
	float destinationRotationYTable[] =
	{
		std::numbers::pi_v<float> / 2.0f,
		std::numbers::pi_v<float> * 3.0f / 2.0f
	};

	float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
	worldTransform_.rotation_.y = destinationRotationY;
}
void Player::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
;
