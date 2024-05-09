#pragma once
#include "stdint.h"
#include "vector"


//size of 1 block
static inline const float kBlockWidth = 1.0f;
static inline const float kBlock_Height = 1.0f;
//amount of blocks
static inline const uint32_t kNumBlockVertical = 20;
static inline const uint32_t kNumBlockHorizontal = 100;

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

	void Initialize();

	void ResetMapChipData();

private:

	MapChipData mapChipData_;


};

