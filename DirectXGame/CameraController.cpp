#include "CameraController.h"
#include "Player.h"
void CameraController::Initialize()
{
	viewProjection_.Initialize();
}

void CameraController::Update()
{
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	//calculate where the camera is related to the world camera
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
	viewProjection_.translation_.x = min(viewProjection_.translation_.x, moveableArea_.left);
	viewProjection_.translation_.x = max(viewProjection_.translation_.x, moveableArea_.right);
	viewProjection_.translation_.y = min(viewProjection_.translation_.y, moveableArea_.bottom);
	viewProjection_.translation_.y = max(viewProjection_.translation_.y, moveableArea_.top);
	viewProjection_.UpdateMatrix();
}

void CameraController::Reset()
{
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	//calculate where the camera is related to the world camera
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
	//viewProjection_.UpdateMatrix();
}

