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

	void RotateSpikeUpsideDown();

	void RotateSpike90Degrees();

	void MovingSpikes();

	void MovingSpikesSideways();

	void MovingSpikesRightEnd();

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void Timer();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	void SetStruct(SpikesStruct spikeStruct) { spikeStruct_ = spikeStruct; };

	SpikesStruct GetStruct() { return spikeStruct_; };

	void SetMove(bool move) { move_ = move; };

	bool GetMove() { return move_; };

	void SetRotateUpsideDown(bool rotate) { rotateUpDown_ = rotate; };

	bool GetRotateUpsideDown() { return rotateUpDown_; };

	void SetStartPosition(float newPos) { movingStartPosition = newPos; };

	void SetAmplitude(float amplitude) { amplitude_ = amplitude; };

	void SetRotateRight(bool rotateRight) { rotateRight_ = rotateRight; };

	void SetMoveRight(bool moveRight) { moveRight_ = moveRight; };

	void SetMaxDistance(float setRight) { maxRightDistance_ = setRight; };

	void SetSpeed(float speed) { speed_ = speed; };

	void SetRotation(float rotate) { rotate_ = rotate; };

	void SetUsesTimer(bool usesTimer) { usesTimer_ = usesTimer; };

	void SetUsesSpikeTimer(bool usesSpikeTimer) { usesSpikeTimer_ = usesSpikeTimer; };

	void SetMayMove(bool mayMove) { mayMove_ = mayMove; };

	bool GetRotateRight() { return rotateRight_; };

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
	int spikeMaxTimer = 30;
	Vector3 startPos;
	float theta = 0.0f;
	float amplitude_ = 12.0f;
	float movingStartPosition = 15.0f;
	float movingStartPositionAdd = {};
	float maxRightDistance_ = {};
	float rotate_ = {};
	float speed_ = {};
	int timer_ = 0;
	bool move_ = false;
	bool rotateUpDown_ = false;
	bool rotateRight_ = false;
	bool moveRight_ = false;
	bool moveRightEnd_ = false;
	bool mayMove_ = false;
	bool usesTimer_ = false;
	bool usesSpikeTimer_ = false;
};

