#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "struct.h"

class MapChipField;

class ReverseCubes
{
public:

	ReverseCubes();

	~ReverseCubes();

	void Initialize(ViewProjection* viewProjection, const Vector3& position, bool isReversedCube);

	void Update();

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	bool GetIsReversed() { return isReversedCube_;};

	//void OnCollision(const Player* player);

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	static inline const float kWidth = 1.8f;
	static inline const float kHeight = 1.8f;
	bool isReversedCube_ = false;
	Model* reversedCubeModel[2] =
	{
		Model::CreateFromOBJ("reversedcube", true),
		Model::CreateFromOBJ("notreversedcube", true),
	};
};

