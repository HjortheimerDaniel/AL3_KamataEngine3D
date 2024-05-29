#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"

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

	void Initialize();

	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVertical() { return kNumBlockVertical; };

	uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; };

	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);

	void Update();

	void Draw();

	

	private:

		//Size of 1 block
		static inline const float kBlockWidth = 2.0f;
		static inline const float kBlockHeight = 2.0f;

		//amount of blocks
		static inline const uint32_t kNumBlockVertical = 20;
		static inline const uint32_t kNumBlockHorizontal = 100;

		MapChipData mapChipData_;
};

