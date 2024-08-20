#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include "struct.h"

class MapChipField;

class Spikes
{
public:

	Spikes();

	~Spikes();
	
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void SpikeTimer();

	void SpikeState();

	void RotateSpike();

	void MovingSpikes();

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	void SetStruct(SpikesStruct spikeStruct) { spikeStruct_ = spikeStruct; };

	SpikesStruct GetStruct() { return spikeStruct_; };

	void SetMove(bool move) { move_ = move; };

	bool GetMove() { return move_; };

	void SetRotate(bool rotate) { rotate_ = rotate; };

	bool GetRotate() { return rotate_; };

	void SetStartPosition(float newPos) { movingStartPosition = newPos; };

	void SetAmplitude(float amplitude) { amplitude_ = amplitude; };

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	static inline const float kWidth = 1.8f;
	static inline const float kHeight = 1.8f;
	SpikesStruct spikeStruct_;
	int spikeTimer = 0;
	int spikeMaxTimer = 50;
	Vector3 startPos;
	float theta = 0.0f;
	float amplitude_ = 12.0f;
	float movingStartPosition = 15.0f;
	float movingStartPositionAdd = {};
	bool move_ = false;
	bool rotate_ = false;
};

