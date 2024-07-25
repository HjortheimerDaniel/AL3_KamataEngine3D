#pragma once
#include "Vector3.h"
#define MAXENEMIES 3

struct AABB {
	Vector3 min;
	Vector3 max;
};

enum class Phase
{
	kFadeIn,
	kPlay,
	kDeath,
	kFadeOut,
};

enum class LRDirection
{
	kRight,
	kLeft
};

struct CollisionMapInfo
{
	bool isHittingCeiling = false;
	bool isOnFloor = false;
	bool isHittingLeftWall = false;
	bool isHittingRightWall = false;
	Vector3 movement;
};



enum Corner
{
	kRightBottom,
	kLeftBottom,
	kRightTop,
	kLeftTop,
	kNumCorner
};