#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include "struct.h"

class MapChipField;

class Parachute
{
public:

	Parachute();

	~Parachute();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();


private:

	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_;


};

