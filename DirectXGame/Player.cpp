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
	//worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f; //rotate the model, change the way its facing
	
}
void Player::Update()
{
	worldTransform_.TransferMatrix();
	
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
			acceleration.x += kAcceleration;
		} 
		else if(Input::GetInstance()->PushKey(DIK_LEFT))
		{
			acceleration.x -= kAcceleration;

		}
		
		//no matter if we press LEFT or RIGHT we pass here
		velocity_.x += acceleration.x; 
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed); //set the limit for the map speed and min speed

		worldTransform_.translation_.x += velocity_.x;
	}
	else 
	{
		velocity_.x *= (1.0f - kAttenuation);
		
	}
	worldTransform_.UpdateMatrix();
}
void Player::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
;
