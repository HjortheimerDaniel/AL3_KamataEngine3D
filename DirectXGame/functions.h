#pragma once
#include <numbers>
#include "algorithm"
#include <iostream>

float EaseInOut(float x);

float EaseInSine(float frameX, float startX, float endX, float endFrameX);

float NormalizeAngle(float angle);

float AngleDifference(float from, float to);