#include "CameraController.h"
#include "Player.h"

void CameraController::Initialize()
{
	viewProjection_.Initialize();
}

void CameraController::Update()
{
	/*ImGui::Begin("View");
	ImGui::DragFloat3("view", &viewProjection_.rotation_.y, 0.01f);
	ImGui::End();*/
	if (isReversed_) 
	{
		if (viewProjection_.rotation_.y <= 3.1f) 
		{
			viewProjection_.rotation_.y += 0.2f;

		}
		if (viewProjection_.rotation_.y >= 3.1f) 
		{
			viewProjection_.rotation_.y = 3.1f;
		}

	}
	else 
	{
		if (viewProjection_.rotation_.y >= 0.0f)
		{
			viewProjection_.rotation_.y -= 0.2f;

		}
		if (viewProjection_.rotation_.y <= 0.0f)
		{
			viewProjection_.rotation_.y = 0.0f;
		}
	}
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	if (target_->GetVelocity().x > 0.5f) {
		printf("");
	}
	targetPosition = targetWorldTransform.translation_ + targetOffset_ + target_->GetVelocity().x * kVelocityBias;

	viewProjection_.translation_ = Lerp(viewProjection_.translation_, targetPosition, kInterpolationRate);

	//calculate where the camera is related to the world camera
	//viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
	viewProjection_.translation_.x = max(viewProjection_.translation_.x, targetWorldTransform.translation_ .x + margin.left);
	viewProjection_.translation_.x = min(viewProjection_.translation_.x, targetWorldTransform.translation_.x + margin.right);
	viewProjection_.translation_.y = max(viewProjection_.translation_.y, targetWorldTransform.translation_.y + margin.bottom);
	viewProjection_.translation_.y = min(viewProjection_.translation_.y, targetWorldTransform.translation_.y + margin.top);

	if (!stageClearCamera_)
	{
		viewProjection_.translation_.x = min(viewProjection_.translation_.x, moveableArea_.left);
		viewProjection_.translation_.x = max(viewProjection_.translation_.x, moveableArea_.right);
		viewProjection_.translation_.y = min(viewProjection_.translation_.y, moveableArea_.bottom);
		viewProjection_.translation_.y = max(viewProjection_.translation_.y, moveableArea_.top);
	}
	viewProjection_.UpdateMatrix();
}

void CameraController::Reset()
{
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	//calculate where the camera is related to the world camera
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
	//viewProjection_.UpdateMatrix();
}

Vector3 CameraController::Lerp(const Vector3& a, const Vector3& b, float t)
{
	Vector3 p{};
	p.x = (1.0f - t) * a.x + t * b.x;
	p.y = (1.0f - t) * a.y + t * b.y;
	p.z = (1.0f - t) * a.z + t * b.z;
	return p;
}

