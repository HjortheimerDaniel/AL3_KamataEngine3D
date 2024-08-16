#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "CameraController.h"

struct IndexSet {
	uint32_t xIndex;
	uint32_t yIndex;
};

enum class MapChipType {
	kBlank,
	kBlock,
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};


class MapChipField
{
	public:

	MapChipField();

	~MapChipField();

	void Initialize(uint32_t numBlockHorizontal, uint32_t numBlockVertical);

	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVertical() { return kNumBlockVertical_; };

	uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal_; };

	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);

	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

	void Update();

	void Draw();

	

	private:

		//Size of 1 block
		static inline const float kBlockWidth = 2.0f;
		static inline const float kBlockHeight = 2.0f;

		//amount of blocks
		static inline uint32_t kNumBlockVertical_ = 100;
		static inline uint32_t kNumBlockHorizontal_ = 100;

		MapChipData mapChipData_;
};

