#pragma once
#include "Vector3.h"
#define MAXENEMIES 4
#define MAXSPIKES 3
#define MAXSPIKES2 194
#define MAXWINDS 5
#define MAXTHANKYOU 12
#define MAXFIREWORKS 4

struct AABB {
	Vector3 min;
	Vector3 max;
};

enum class Phase
{
	kFadeIn,
	kPlay,
	kDeath,
	kStageClear,
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

enum class SpikesStruct
{
	Inactive,
	Awake,
	Active,
	Return,
};



enum Corner
{
	kRightBottom,
	kLeftBottom,
	kRightTop,
	kLeftTop,
	kNumCorner
};

struct SpikeSpawnConfig {
	int loopStartX; 
	int loodEndX;
	int baseX;
	int baseY;
	int incrementX;
	int incrementY;
};

struct MovingSpikeSettings {

	bool move;
	bool rotate;
	float amplitude;
	float startPositionOffset;
};

enum class Scene
{
	kUnknown = 0,
	kTitle,
	kGame,
	kGame2,
	kGame3,
	kGameClear,
};