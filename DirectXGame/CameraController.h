#pragma once
#include "ViewProjection.h"

class Player;

struct Rect //limit the cameras movement
{
	float left = 0.0f;
	float right = 1.0f;
	float bottom = 0.0f;
	float top = 1.0f;
};



class CameraController
{
	public:
		void Initialize();

		void Update();

		void SetTarget(Player* target) { target_ = target; };

		void Reset();

		const ViewProjection& GetViewProjection() { return viewProjection_; }

		void SetMoveableArea(Rect area) { moveableArea_ = area; };

	private:

		ViewProjection viewProjection_;
		Player* target_ = nullptr;
		Vector3 targetOffset_ = { 0.0f,0.0f,-40.0f }; //how far away from the player do we want the camera to be
		Rect moveableArea_ = { 0,100,0,100 };

};

