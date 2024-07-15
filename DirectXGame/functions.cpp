#include "functions.h"

float EaseInOut(float x)
{
    float pi = std::numbers::pi_v<float>;
    return -(cosf(pi * x) - 1) / 2;
}

float EaseInSine(float frameX, float startX, float endX, float endFrameX)
{
    float t = frameX / endFrameX; // Normalize the frameX to [0, 1]
    float easedT = EaseInOut(t);
    return startX + easedT * (endX - startX);
}

float NormalizeAngle(float angle)
{
    while (angle > std::numbers::pi_v<float>) {
        angle -= 2.0f * std::numbers::pi_v<float>;
    }
    while (angle < -std::numbers::pi_v<float>) {
        angle += 2.0f * std::numbers::pi_v<float>;
    }
    return angle;
}

float AngleDifference(float from, float to)
{
    float diff = NormalizeAngle(to - from);
    return diff;
}
